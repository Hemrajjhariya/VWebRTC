#import "VCXClient.h"
#import "VCXSignalingChannel.h"
#import "VCXSignalingMessage.h"

@interface VCXClient () <VCXSignalingChannelDelegate, RTCPeerConnectionDelegate>

@property(nonatomic, strong) RTCPeerConnection *peerConnection;
@property(nonatomic, strong) RTCPeerConnectionFactory *factory;
@property(nonatomic, strong) NSMutableArray *messageQueue;
@property(nonatomic, assign) BOOL hasReceivedSdp;
@property(nonatomic, strong) VCXSignalingChannel *signalingChannel;
@property(nonatomic, assign) BOOL isInitiator;
@property(nonatomic, strong) NSMutableArray *iceServers;
@property(nonatomic, strong) RTCMediaConstraints *defaultPeerConnectionConstraints;


@end
