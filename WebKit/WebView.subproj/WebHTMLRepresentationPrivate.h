/*	
    IFHTMLRepresentationPrivate.h
	Copyright 2002, Apple, Inc. All rights reserved.
*/

#import <WebKit/IFHTMLRepresentation.h>

@interface IFHTMLRepresentation (IFPrivate)
- (IFWebCoreBridge *)_bridge;
- (KHTMLPart *)part;
@end
