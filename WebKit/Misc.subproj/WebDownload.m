/*	WebDownload.m
        Copyright 2003, Apple, Inc. All rights reserved.
*/

#import <WebKit/WebDownload.h>

#import <Foundation/NSURLAuthenticationChallenge.h>
#import <Foundation/NSURLDownload.h>
#import <Foundation/NSURLDownloadPrivate.h>
#import <WebKit/WebAssertions.h>
#import <WebKit/WebPanelAuthenticationHandler.h>

// FIXME: Remove these declarations because _initWithLoadingConnection is declared in NSURLDownloadPrivate.h
// and _initWithLoadingResource is obsolete, once we compile only with the new Foundation.
@interface NSURLDownload (WebDownloadCapability)
- (id)_initWithLoadingConnection:(NSURLConnection *)connection
                         request:(NSURLRequest *)request
                        response:(NSURLResponse *)response
                        delegate:(id)delegate
                           proxy:(NSURLConnectionDelegateProxy *)proxy;
- (id)_initWithLoadingResource:(NSURLConnection *)connection
                       request:(NSURLRequest *)request
                      response:(NSURLResponse *)response
                      delegate:(id)delegate
                         proxy:(NSURLConnectionDelegateProxy *)proxy;
@end

@interface WebDownloadInternal : NSObject
{
@public
    id realDelegate;
}

- (void)setRealDelegate:(id)rd;

@end

@implementation WebDownloadInternal

- (void)dealloc
{
    [realDelegate release];
    [super dealloc];
}

- (void)setRealDelegate:(id)rd
{
    [rd retain];
    [realDelegate release];
    realDelegate = rd;
}

- (BOOL)respondsToSelector:(SEL)selector
{
    if (selector == @selector(downloadDidBegin:) ||
	selector == @selector(download:willSendRequest:redirectResponse:) ||
	selector == @selector(download:didReceiveResponse:) ||
	selector == @selector(download:didReceiveDataOfLength:) ||
	selector == @selector(download:shouldDecodeSourceDataOfMIMEType:) ||
	selector == @selector(download:decideDestinationWithSuggestedFilename:) ||
	selector == @selector(download:didCreateDestination:) ||
	selector == @selector(downloadDidFinish:) ||
	selector == @selector(download:didFailWithError:) ||
	selector == @selector(download:shouldBeginChildDownloadOfSource:delegate:) ||
	selector == @selector(download:didBeginChildDownload:)) {
	return [realDelegate respondsToSelector:selector];
    }

    return [super respondsToSelector:selector];
}

- (void)downloadDidBegin:(NSURLDownload *)download
{
    [realDelegate downloadDidBegin:download];
}

- (NSURLRequest *)download:(NSURLDownload *)download willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse
{
    return [realDelegate download:download willSendRequest:request redirectResponse:redirectResponse];
}

- (void)download:(NSURLDownload *)download didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge
{
    if ([realDelegate respondsToSelector:@selector(download:didReceiveAuthenticationChallenge:)]) {
	[realDelegate download:download didReceiveAuthenticationChallenge:challenge];
    } else {
	NSWindow *window = nil;
	if ([realDelegate respondsToSelector:@selector(downloadWindowForAuthenticationSheet:)]) {
	    window = [realDelegate downloadWindowForAuthenticationSheet:(WebDownload *)download];
	}

	[[WebPanelAuthenticationHandler sharedHandler] startAuthentication:challenge window:window];
    }
}

- (void)download:(NSURLDownload *)download didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge
{
    if ([realDelegate respondsToSelector:@selector(download:didCancelAuthenticationChallenge:)]) {
	[realDelegate download:download didCancelAuthenticationChallenge:challenge];
    } else {
	[[WebPanelAuthenticationHandler sharedHandler] cancelAuthentication:challenge];
    }
}

- (void)download:(NSURLDownload *)download didReceiveResponse:(NSURLResponse *)response
{
    [realDelegate download:download didReceiveResponse:response];
}

- (void)download:(NSURLDownload *)download didReceiveDataOfLength:(unsigned)length
{
    [realDelegate download:download didReceiveDataOfLength:length];
}

- (BOOL)download:(NSURLDownload *)download shouldDecodeSourceDataOfMIMEType:(NSString *)encodingType
{
    return [realDelegate download:download shouldDecodeSourceDataOfMIMEType:encodingType];
}

- (void)download:(NSURLDownload *)download decideDestinationWithSuggestedFilename:(NSString *)filename
{
    [realDelegate download:download decideDestinationWithSuggestedFilename:filename];
}

- (void)download:(NSURLDownload *)download didCreateDestination:(NSString *)path
{
    [realDelegate download:download didCreateDestination:path];
}

- (void)downloadDidFinish:(NSURLDownload *)download
{
    [realDelegate downloadDidFinish:download];
}

- (void)download:(NSURLDownload *)download didFailWithError:(NSError *)error
{
    [realDelegate download:download didFailWithError:error];
}

- (NSURLRequest *)download:(NSURLDownload *)download shouldBeginChildDownloadOfSource:(NSURLRequest *)child delegate:(id *)childDelegate
{
    return [realDelegate download:download shouldBeginChildDownloadOfSource:child delegate:childDelegate];
}

- (void)download:(NSURLDownload *)parent didBeginChildDownload:(NSURLDownload *)child
{
    [realDelegate download:parent didBeginChildDownload:child];
}

@end

@implementation WebDownload

- (void)_setRealDelegate:(id)delegate
{
    if (_webInternal == nil) {
        _webInternal = [[WebDownloadInternal alloc] init];
        [_webInternal setRealDelegate:delegate];
    } else {
        ASSERT(_webInternal == delegate);
    }
}

- (id)init
{
    self = [super init];
    if (self != nil) {
        // _webInternal can be set up before init by _setRealDelegate
	if (_webInternal == nil) {
            _webInternal = [[WebDownloadInternal alloc] init];
        }
    }
    return self;
}

- (void)dealloc
{
    [_webInternal release];
    [super dealloc];
}

- (id)initWithRequest:(NSURLRequest *)request delegate:(id)delegate
{
    [self _setRealDelegate:delegate];
    return [super initWithRequest:request delegate:_webInternal];
}

- (id)_initWithLoadingConnection:(NSURLConnection *)connection
                         request:(NSURLRequest *)request
                        response:(NSURLResponse *)response
                        delegate:(id)delegate
                           proxy:(NSURLConnectionDelegateProxy *)proxy
{
    [self _setRealDelegate:delegate];
    return [super _initWithLoadingConnection:connection request:request response:response delegate:_webInternal proxy:proxy];
}

// FIXME: Remove this override because it no longer exists in newer Foundations.
- (id)_initWithLoadingResource:(NSURLConnection *)connection
                       request:(NSURLRequest *)request
                      response:(NSURLResponse *)response
                      delegate:(id)delegate
                         proxy:(NSURLConnectionDelegateProxy *)proxy
{
    [self _setRealDelegate:delegate];
    return [super _initWithLoadingResource:connection request:request response:response delegate:_webInternal proxy:proxy];
}

- (id)_initWithRequest:(NSURLRequest *)request
              delegate:(id)delegate
             directory:(NSString *)directory
{
    [self _setRealDelegate:delegate];
    return [super _initWithRequest:request delegate:_webInternal directory:directory];
}

@end
