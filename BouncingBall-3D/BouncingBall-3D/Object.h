#pragma once

#define GRAVITATIONAL_ACCELERATION 9.8

class Object {
public:
	virtual ~Object() = default;
	virtual void update() = 0;
	virtual void restart() = 0;
	virtual void stop() = 0;
	virtual void reset() = 0;
};
