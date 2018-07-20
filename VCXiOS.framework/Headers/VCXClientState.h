/**
 @enum VCXClientState
 */
typedef NS_ENUM(NSInteger, VCXClientState) {
    /// Disconnected
    VCXClientStateDisconnected,
    /// Ready to signaling
    VCXClientStateReady,
    /// Signaling proccess
    VCXClientStateConnecting,
    /// Signlaning done
    VCXClientStateConnected,
};
