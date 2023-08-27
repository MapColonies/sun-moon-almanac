#include <nan.h>
#include <node.h>

#include "./lib/MoonIluminationCalculator.h"
#include "./lib/Location.h"
#include "./lib/DateTime.h"
#include "./lib/MoonIluminationData.h"

namespace sunmoon
{
    using v8::Context;
    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::NewStringType;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Value;

    MoonIluminationCalculator _moonIluminationCalculator;

    void invalidArgument(Isolate *isolate, std::string argumentName) {
        std::string message = "Argument \"" + argumentName + "\"is invalid";
        Local<String> localMessage = String::NewFromUtf8(isolate, message.c_str(), NewStringType::kNormal).ToLocalChecked();
        isolate->ThrowException(Exception::TypeError(localMessage));
    }

    double getNumberFromObject(Isolate *isolate, Local<Object> obj, std::string propName)
    {
        Local<String> prop = Nan::New(propName).ToLocalChecked();

        // Check HasOwnProperty
        if (!Nan::HasOwnProperty(obj, prop).FromJust())
        {
            invalidArgument(isolate, propName);
        }

        Local<Value> value = Nan::Get(obj, prop).ToLocalChecked();

        // Check that property is a number
        if (!value->IsNumber())
        {
            invalidArgument(isolate, propName);
        }

        return value->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    }

    void RegisterPropOnObject(Local<Object> obj, std::string key, Local<Value> value)
    {
        Local<String> prop = Nan::New(key).ToLocalChecked();
        Nan::Set(obj, prop, value);
    }

    void CalculateMoonStats(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        Local<Object> location = args[0]->ToObject(context).ToLocalChecked();
        Local<Object> date = args[1]->ToObject(context).ToLocalChecked();

        double lon, lat, height;
        int year, month, day, hour, minute, second;
        lon = getNumberFromObject(isolate, location, "lon");
        lat = getNumberFromObject(isolate, location, "lat");
        height = getNumberFromObject(isolate, location, "height");

        year = (int)getNumberFromObject(isolate, date, "year");
        month = (int)getNumberFromObject(isolate, date, "month");
        day = (int)getNumberFromObject(isolate, date, "day");
        hour = (int)getNumberFromObject(isolate, date, "hour");
        minute = (int)getNumberFromObject(isolate, date, "minute");
        second = (int)getNumberFromObject(isolate, date, "second");

        MoonIluminationData moonData = _moonIluminationCalculator.calculate(
            Location(lon, lat, height),
            DateTime(year, month, day, hour, minute, second));

        Local<Object> moon = Nan::New<Object>();

        RegisterPropOnObject(moon, "elevation", Nan::New(moonData.getMoonElevation()));
        RegisterPropOnObject(moon, "azimuth", Nan::New(moonData.getMoonAzimuth()));
        RegisterPropOnObject(moon, "illuminationPercentage", Nan::New(moonData.getMoonIluminationPercentage()));

        args.GetReturnValue().Set(moon);
    }

    void Initialize(Local<Object> exports)
    {
        NODE_SET_METHOD(exports, "calculateMoonStats", CalculateMoonStats);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
} // namespace sunmoon
