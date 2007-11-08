/*
 * Copyright (C) 2005 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2005 Ben La Monica <ben.lamonica@gmail.com>.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#import <Foundation/Foundation.h>
#import <QuartzCore/CoreImage.h>
#import <AppKit/NSBitmapImageRep.h>
#import <AppKit/NSGraphicsContext.h>
#import <AppKit/NSCIImageRep.h>

#import <getopt.h>

/* prototypes */
int main(int argc, const char *argv[]);
CGImageRef createImageFromStdin(int imageSize);
void compareImages(CGImageRef actualBitmap, CGImageRef baselineImage, unsigned threshold);
NSBitmapImageRep *getDifferenceBitmap(CGImageRef actualBitmap, CGImageRef baselineImage);
float computePercentageDifferent(NSBitmapImageRep *diffBitmap, unsigned threshold);


int main(int argc, const char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    unsigned threshold = 0;

    struct option options[] = {
        {"threshold", required_argument, NULL, 't'},
        {NULL, 0, NULL, 0}
    };

    int option;
    while ((option = getopt_long(argc, (char * const *)argv, "", options, NULL)) != -1) {
        switch (option) {
        case 't':
            threshold = strtol(optarg, NULL, 0);
            break;
        case '?':   // unknown or ambiguous option
        case ':':   // missing argument
            exit(1);
            break;
        }
    }
    
    char buffer[2048];
    CGImageRef actualImage = nil;
    CGImageRef baselineImage = nil;

    NSAutoreleasePool *innerPool = [[NSAutoreleasePool alloc] init];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // remove the CR
        char *newLineCharacter = strchr(buffer, '\n');
        if (newLineCharacter) {
            *newLineCharacter = '\0';
        }
        
        if (strncmp("Content-length: ", buffer, 16) == 0) {
            strtok(buffer, " ");
            int imageSize = strtol(strtok(NULL, " "), NULL, 10);

            if(imageSize > 0 && actualImage == nil) 
                actualImage = createImageFromStdin(imageSize);
            else if (imageSize > 0 && baselineImage == nil)
                baselineImage = createImageFromStdin(imageSize);
            else
                fputs("error, image size must be specified.\n", stdout);
        }

        if (actualImage != nil && baselineImage != nil) {
            compareImages(actualImage, baselineImage, threshold);
            CGImageRelease(actualImage);
            CGImageRelease(baselineImage);
            actualImage = nil;
            baselineImage = nil;
            [innerPool release];
            innerPool = [[NSAutoreleasePool alloc] init];
        }
        
        fflush(stdout);
    }
    [innerPool release];
    
    [pool release];
    return 0;
}

CGImageRef createImageFromStdin(int bytesRemaining)
{
    unsigned char buffer[2048];
    NSMutableData *data = [[NSMutableData alloc] initWithCapacity:bytesRemaining];
    
    int bytesRead = 0;
    while (bytesRemaining > 0) {
        bytesRead = (bytesRemaining > 2048 ? 2048 : bytesRemaining);
        fread(buffer, bytesRead, 1, stdin);
        [data appendBytes:buffer length:bytesRead];
        bytesRemaining -= bytesRead;
    }
    CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData((CFDataRef)data);
    CGImageRef image = CGImageCreateWithPNGDataProvider(dataProvider, NULL, NO, kCGRenderingIntentDefault);
    [data release];
    CGDataProviderRelease(dataProvider);
    
    return image; 
}

void compareImages(CGImageRef actualBitmap, CGImageRef baselineBitmap, unsigned threshold)
{
    // prepare the difference blend to check for pixel variations
    NSBitmapImageRep *diffBitmap = getDifferenceBitmap(actualBitmap, baselineBitmap);
            
    float percentage = computePercentageDifferent(diffBitmap, threshold);
    
    percentage = (float)((int)(percentage * 100.0f)) / 100.0f; // round to 2 decimal places
    
    // send message to let them know if an image was wrong
    if (percentage > 0.0) {
        // since the diff might actually show something, send it to stdout
        NSData *diffPNGData = [diffBitmap representationUsingType:NSPNGFileType properties:nil];
        fprintf(stdout, "Content-length: %d\n", [diffPNGData length]);
        fwrite([diffPNGData bytes], [diffPNGData length], 1, stdout);
        fprintf(stdout, "diff: %01.2f%% failed\n", percentage);
    } else
        fprintf(stdout, "diff: %01.2f%% passed\n", percentage);
}

NSBitmapImageRep *getDifferenceBitmap(CGImageRef testBitmap, CGImageRef referenceBitmap)
{
    // we must have both images to take diff
    if (testBitmap == nil || referenceBitmap == nil)
        return nil;

    NSBitmapImageRep *diffBitmap = [NSBitmapImageRep alloc];
    [diffBitmap initWithBitmapDataPlanes:NULL
                              pixelsWide:CGImageGetWidth(testBitmap)
                              pixelsHigh:CGImageGetHeight(testBitmap)
                           bitsPerSample:CGImageGetBitsPerComponent(testBitmap)
                         samplesPerPixel:CGImageGetBitsPerPixel(testBitmap) / CGImageGetBitsPerComponent(testBitmap)
                                hasAlpha:YES
                                isPlanar:NO
                          colorSpaceName:NSCalibratedRGBColorSpace
                            bitmapFormat:0
                             bytesPerRow:CGImageGetBytesPerRow(testBitmap)
                            bitsPerPixel:CGImageGetBitsPerPixel(testBitmap)
    ];

    NSGraphicsContext *nsContext = [NSGraphicsContext graphicsContextWithBitmapImageRep:diffBitmap];
    CGContextRef cgContext = [nsContext graphicsPort];
    CGContextSetBlendMode(cgContext, kCGBlendModeNormal);
    CGContextDrawImage(cgContext, CGRectMake(0, 0, CGImageGetWidth(testBitmap), CGImageGetHeight(testBitmap)), testBitmap);
    CGContextSetBlendMode(cgContext, kCGBlendModeDifference);
    CGContextDrawImage(cgContext, CGRectMake(0, 0, CGImageGetWidth(referenceBitmap), CGImageGetHeight(referenceBitmap)), referenceBitmap);

    return [diffBitmap autorelease];
}

/**
 * Counts the number of non-black pixels, and returns the percentage
 * of non-black pixels to total pixels in the image.
 */
float computePercentageDifferent(NSBitmapImageRep *diffBitmap, unsigned threshold)
{
    // if diffBiatmap is nil, then there was an error, and it didn't match.
    if (diffBitmap == nil)
        return 100.0f;
    
    unsigned bitmapFormat = [diffBitmap bitmapFormat];
    assert(!(bitmapFormat & NSAlphaFirstBitmapFormat));
    assert(!(bitmapFormat & NSFloatingPointSamplesBitmapFormat));
    
    unsigned pixelsHigh = [diffBitmap pixelsHigh];
    unsigned pixelsWide = [diffBitmap pixelsWide];
    unsigned bytesPerRow = [diffBitmap bytesPerRow];
    unsigned char *pixelRowData = [diffBitmap bitmapData];
    unsigned differences = 0;
    
    // NOTE: This may not be safe when switching between ENDIAN types
    for (unsigned row = 0; row < pixelsHigh; row++) {
        for (unsigned col = 0; col < (pixelsWide * 4); col += 4) {
            unsigned char* red = pixelRowData + col;
            unsigned char* green = red + 1;
            unsigned char* blue = red + 2;
            unsigned distance = *red + *green + *blue;
            if (distance > threshold) {
                differences++;
                // shift the pixels towards white to make them more visible
                *red = MIN(UCHAR_MAX, *red + 100);
                *green = MIN(UCHAR_MAX, *green + 100);
                *blue = MIN(UCHAR_MAX, *blue + 100);
            }
        }
        pixelRowData += bytesPerRow;
    }
    
    float totalPixels = pixelsHigh * pixelsWide;
    return (differences * 100.f) / totalPixels;
}
