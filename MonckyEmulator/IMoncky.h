#pragma once
#include <memory>

#include "cl.h"
#include "registers.h"


class IMoncky {
private:
	std::unique_ptr<RegisterPool> registers;
	std::unique_ptr<ControlLogic> cl;
public:
	virtual ~IMoncky() {}
};