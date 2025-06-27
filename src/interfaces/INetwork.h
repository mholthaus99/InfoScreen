#pragma once

class INetwork {
     public:
         
          virtual void connect() = 0;
          virtual bool isConnected() = 0;
          virtual ~INetwork(){};
};