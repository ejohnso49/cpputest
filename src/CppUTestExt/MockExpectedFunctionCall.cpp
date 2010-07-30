/*
 * Copyright (c) 2007, Michael Feathers, James Grenning and Bas Vodde
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockExpectedFunctionCall.h"

MockExpectedFunctionCall::MockExpectedFunctionCall() : parameters_(NULL), fulfilled_(false)
{
}

MockExpectedFunctionCall::~MockExpectedFunctionCall()
{
	while (parameters_) {
		MockFunctionParameter* next = parameters_->nextParameter;
		delete parameters_;
		parameters_ = next;
	}
}

MockFunctionCall* MockExpectedFunctionCall::withName(const SimpleString& name)
{
	name_ = name;
	return this;
}

MockFunctionCall* MockExpectedFunctionCall::withParameter(const SimpleString& name, int value)
{
	parameters_ = new MockFunctionParameter(name, MOCK_FUNCTION_PARAMETER_INT, parameters_);
	parameters_->value_.intValue_ = value;
	return this;
}

MockFunctionCall* MockExpectedFunctionCall::withParameter(const SimpleString& name, double value)
{
	parameters_ = new MockFunctionParameter(name, MOCK_FUNCTION_PARAMETER_DOUBLE, parameters_);
	parameters_->value_.doubleValue_ = value;
	return this;
}

MockFunctionCall* MockExpectedFunctionCall::withParameter(const SimpleString& name, const char* value)
{
	parameters_ = new MockFunctionParameter(name, MOCK_FUNCTION_PARAMETER_STRING, parameters_);
	parameters_->value_.stringValue_ = value;
	return this;
}

MockFunctionCall* MockExpectedFunctionCall::withParameter(const SimpleString& name, void* value)
{
	parameters_ = new MockFunctionParameter(name, MOCK_FUNCTION_PARAMETER_POINTER, parameters_);
	parameters_->value_.pointerValue_ = value;
	return this;
}

MockFunctionParameterType MockExpectedFunctionCall::getParameterType(const SimpleString& name)
{
	for (MockFunctionParameter * p = parameters_; p; p = p->nextParameter) {
		if (p->name_ == name)
			return p->type_;
	}
	return MOCK_FUNCTION_PARAMETER_NONE;
}

MockParameterValue MockExpectedFunctionCall::getParameterValue(const SimpleString& name)
{
	for (MockFunctionParameter * p = parameters_; p; p = p->nextParameter) {
		if (p->name_ == name)
			return p->value_;
	}
	MockParameterValue defaultValue;
	defaultValue.intValue_ = 0;
	return defaultValue;
}

bool MockExpectedFunctionCall::isFulfilled()
{
	return fulfilled_;
}

void MockExpectedFunctionCall::setFulfilled()
{
	fulfilled_ = true;
}

SimpleString MockExpectedFunctionCall::toString()
{
	return name_;
}

bool MockExpectedFunctionCall::relatesTo(const SimpleString& functionName)
{
	return functionName == name_;
}