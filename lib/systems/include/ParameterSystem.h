#pragma once
#include <unordered_map>

namespace Parameters {

class FloatParameter {
public:
    virtual float get() const = 0;
    virtual void set(float value) = 0;
    virtual ~FloatParameter() {}
};

class BoolParameter {
public:
    virtual bool get() const = 0;
    virtual void set(bool value) = 0;
    virtual ~BoolParameter() {}
};

class MaxSpeed : public FloatParameter {
    float value;
public:
    MaxSpeed() : value(120.0) {}
    float get() const override { return value; }
    void set(float v) override { value = v; }
};

class Threshold : public FloatParameter {
    float value;
public:
    Threshold() : value(0.75) {}
    float get() const override { return value; }
    void set(float v) override { value = v; }
};

class IsActive : public BoolParameter {
    bool value;
public:
    IsActive() : value(false) {}
    bool get() const override { return value; }
    void set(bool v) override { value = v; }
};

MaxSpeed MaxSpeedInstance;
Threshold ThresholdInstance;
std::unordered_map<const char *, Parameters::FloatParameter*> floatLookupMap = {
    {"b1fc2577", &MaxSpeedInstance},
    {"0da627ad", &ThresholdInstance},
};

IsActive IsActiveInstance;
std::unordered_map<const char *, Parameters::BoolParameter*> boolLookupMap = {
    {"57401e59", &IsActiveInstance},
};

}