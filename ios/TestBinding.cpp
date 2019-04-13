// Copyright 2004-present Facebook. All Rights Reserved.

#include "TestBinding.h"

#include "Test.h"
#include <jsi/JSIDynamic.h>

namespace facebook {
  namespace react {
    
    static jsi::Object getModule(
                                 jsi::Runtime &runtime,
                                 const std::string &moduleName) {
      auto batchedBridge =
      runtime.global().getPropertyAsObject(runtime, "__fbBatchedBridge");
      auto getCallableModule =
      batchedBridge.getPropertyAsFunction(runtime, "getCallableModule");
      auto module = getCallableModule
      .callWithThis(
                    runtime,
                    batchedBridge,
                    {jsi::String::createFromUtf8(runtime, moduleName)})
      .asObject(runtime);
      return module;
    }
    
    void TestBinding::install(
                                   jsi::Runtime &runtime,
                                   std::shared_ptr<TestBinding> testBinding) {
      auto testModuleName = "nativeTest";
      auto object = jsi::Object::createFromHostObject(runtime, testBinding);
      runtime.global().setProperty(runtime, testModuleName, std::move(object));
    }
    
    TestBinding::TestBinding(std::unique_ptr<Test> test)
    : test_(std::move(test)) {}
  
    jsi::Value TestBinding::get(
                                     jsi::Runtime &runtime,
                                     const jsi::PropNameID &name) {
      auto methodName = name.utf8(runtime);
      auto &test = *test_;
      
      // Semantic: Creates a new node with given pieces.
//      if (methodName == "createNode") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     5,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       return valueFromShadowNode(
//                                                                                  runtime,
//                                                                                  uiManager.createNode(
//                                                                                                       tagFromValue(runtime, arguments[0]),
//                                                                                                       componentNameFromValue(runtime, arguments[1]),
//                                                                                                       surfaceIdFromValue(runtime, arguments[2]),
//                                                                                                       RawProps(runtime, arguments[3]),
//                                                                                                       eventTargetFromValue(runtime, arguments[4], arguments[0])));
//                                                     });
//      }
//
//      // Semantic: Clones the node with *same* props and *same* children.
//      if (methodName == "cloneNode") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     1,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       return valueFromShadowNode(
//                                                                                  runtime,
//                                                                                  uiManager.cloneNode(shadowNodeFromValue(runtime, arguments[0])));
//                                                     });
//      }
//
//      // Semantic: Clones the node with *same* props and *empty* children.
//      if (methodName == "cloneNodeWithNewChildren") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     1,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       return valueFromShadowNode(
//                                                                                  runtime,
//                                                                                  uiManager.cloneNode(
//                                                                                                      shadowNodeFromValue(runtime, arguments[0]),
//                                                                                                      ShadowNode::emptySharedShadowNodeSharedList()));
//                                                     });
//      }
//
//      // Semantic: Clones the node with *given* props and *same* children.
//      if (methodName == "cloneNodeWithNewProps") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     2,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       const auto &rawProps = RawProps(runtime, arguments[1]);
//                                                       return valueFromShadowNode(
//                                                                                  runtime,
//                                                                                  uiManager.cloneNode(
//                                                                                                      shadowNodeFromValue(runtime, arguments[0]),
//                                                                                                      nullptr,
//                                                                                                      &rawProps));
//                                                     });
//      }
//
//      // Semantic: Clones the node with *given* props and *empty* children.
//      if (methodName == "cloneNodeWithNewChildrenAndProps") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     2,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       const auto &rawProps = RawProps(runtime, arguments[1]);
//                                                       return valueFromShadowNode(
//                                                                                  runtime,
//                                                                                  uiManager.cloneNode(
//                                                                                                      shadowNodeFromValue(runtime, arguments[0]),
//                                                                                                      ShadowNode::emptySharedShadowNodeSharedList(),
//                                                                                                      &rawProps));
//                                                     });
//      }
//
//      if (methodName == "appendChild") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     2,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       uiManager.appendChild(
//                                                                             shadowNodeFromValue(runtime, arguments[0]),
//                                                                             shadowNodeFromValue(runtime, arguments[1]));
//                                                       return jsi::Value::undefined();
//                                                     });
//      }
//
//      if (methodName == "createChildSet") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     1,
//                                                     [](jsi::Runtime &runtime,
//                                                        const jsi::Value &thisValue,
//                                                        const jsi::Value *arguments,
//                                                        size_t count) -> jsi::Value {
//                                                       auto shadowNodeList =
//                                                       std::make_shared<SharedShadowNodeList>(SharedShadowNodeList({}));
//                                                       return valueFromShadowNodeList(runtime, shadowNodeList);
//                                                     });
//      }
//
//      if (methodName == "appendChildToSet") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     2,
//                                                     [](jsi::Runtime &runtime,
//                                                        const jsi::Value &thisValue,
//                                                        const jsi::Value *arguments,
//                                                        size_t count) -> jsi::Value {
//                                                       auto shadowNodeList = shadowNodeListFromValue(runtime, arguments[0]);
//                                                       auto shadowNode = shadowNodeFromValue(runtime, arguments[1]);
//                                                       shadowNodeList->push_back(shadowNode);
//                                                       return jsi::Value::undefined();
//                                                     });
//      }
//
//      if (methodName == "completeRoot") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     2,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       uiManager.completeSurface(
//                                                                                 surfaceIdFromValue(runtime, arguments[0]),
//                                                                                 shadowNodeListFromValue(runtime, arguments[1]));
//                                                       return jsi::Value::undefined();
//                                                     });
//      }
//
//      if (methodName == "registerEventHandler") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     1,
//                                                     [this](
//                                                            jsi::Runtime &runtime,
//                                                            const jsi::Value &thisValue,
//                                                            const jsi::Value *arguments,
//                                                            size_t count) -> jsi::Value {
//                                                       auto eventHandler =
//                                                       arguments[0].getObject(runtime).getFunction(runtime);
//                                                       eventHandler_ =
//                                                       std::make_unique<EventHandlerWrapper>(std::move(eventHandler));
//                                                       return jsi::Value::undefined();
//                                                     });
//      }
//
//      if (methodName == "getRelativeLayoutMetrics") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     2,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       auto layoutMetrics = uiManager.getRelativeLayoutMetrics(
//                                                                                                               *shadowNodeFromValue(runtime, arguments[0]),
//                                                                                                               shadowNodeFromValue(runtime, arguments[1]).get());
//                                                       auto frame = layoutMetrics.frame;
//                                                       auto result = jsi::Object(runtime);
//                                                       result.setProperty(runtime, "left", frame.origin.x);
//                                                       result.setProperty(runtime, "top", frame.origin.y);
//                                                       result.setProperty(runtime, "width", frame.size.width);
//                                                       result.setProperty(runtime, "height", frame.size.height);
//                                                       return result;
//                                                     });
//      }
//
//      if (methodName == "setNativeProps") {
//        return jsi::Function::createFromHostFunction(
//                                                     runtime,
//                                                     name,
//                                                     2,
//                                                     [&uiManager](
//                                                                  jsi::Runtime &runtime,
//                                                                  const jsi::Value &thisValue,
//                                                                  const jsi::Value *arguments,
//                                                                  size_t count) -> jsi::Value {
//                                                       uiManager.setNativeProps(
//                                                                                shadowNodeFromValue(runtime, arguments[0]),
//                                                                                RawProps(runtime, arguments[1]));
//
//                                                       return jsi::Value::undefined();
//                                                     });
//      }
      
      return jsi::Value::undefined();
    }
    
  } // namespace react
} // namespace facebook
