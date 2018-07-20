@import WebRTC;
#import "VCXClientState.h"

@class VCXClient;

///-----------------------------------
/// @protocol VCXClientDelegate Protocol
///-----------------------------------

/**
 @protocol VCXClientDelegate

 Classes that implement this protocol will be called for RTC Client
 event notification.

 */
@protocol VCXClientDelegate <NSObject>

- (void)appClient:(VCXClient *)client didChangeState:(VCXClientState)state;
- (void)appClient:(VCXClient *)client didChangeConnectionState:(RTCIceConnectionState)state;
- (void)appClient:(VCXClient *)client didReceiveRemoteStream:(RTCMediaStream *)remoteStream
                                          withStreamId:(NSString *)streamId;
- (void)appClient:(VCXClient *)client didError:(NSError *)error;
- (RTCMediaStream *)streamToPublishByAppClient:(VCXClient *)client;
- (NSDictionary *)appClientRequestICEServers:(VCXClient *)client;

@end
