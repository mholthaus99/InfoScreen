#pragma once

// interfaces/IObject.h
class IObject {
public:
     virtual void init() = 0;
     virtual ~IObject() {}
};

// This interface serves as a base for all objects in the system that require initialization.