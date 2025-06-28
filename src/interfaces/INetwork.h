#pragma once
/**
 * @brief Interface for network connectivity.
 *
 * This abstract class defines the interface for network operations.
 * Classes implementing this interface should provide mechanisms to connect to a network
 * and to check the connection status.
 */
class INetwork {
   public:
    virtual void connect() = 0;
    virtual bool isConnected() = 0;
    virtual ~INetwork() {};
};