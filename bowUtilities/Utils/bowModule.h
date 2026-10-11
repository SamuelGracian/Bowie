/************************************************************************/
/**
 * @file bowModule.h
 * @author Samuel G
 * @date 07/10/2026
 * @brief Represents one engine module.
 * 
 * Represents one engine module. Essentially it is a specialized type of 
 * singleton. Module must be manually started up and shut down before and after
 * use.
 */
 /************************************************************************/
#pragma once
#include <iostream>

#include "bowUtilitiesRequisites.h"

namespace bowEngineSDK
{
/**
* @brief
*  Represents one engine module.
*/
template <class T>

class Module
{
public:

  /*
  * @brief
  *  Returns a reference to the module isntance. Module needs to be started up 
  *  first otherwise an error will be thrown.
  */
  static T&
    instance() {
    if (!isStartedUp()) {
      std::cerr << "Trying to acces a non started module." << std::endl;
    }
    if (isDestroyed()) {
      std::cerr << "Trying to acces a destroyed module" << std::endl;
    }
  }
  return *_instance();
};

/*
* @brief
*  Returns a pointer to the module instance.
*/
static T*
instancePtr() {
  if (!isStartedUp()) {
    std::cerr << "Trying to acces a module that hasnt been started yet." << std::endl;
  }
  if (isDestroyed()) {
    std::cerr << "Trying to acces a destroyed module" << std::endl;
  }
  return _instance();
}

/*
* @brief
*  Constructs and starts the module using the specific parameters.
*/
template<class... Args>
static void
startUp(Args&& ...args) {
  if (isStartedUp()) {
    std::cerr << "Trying to start an already started module" << std::endl;
  }
  _instance() = new T(std::forward<Args>(args)...);
  isStartedUp() = true;

  static_cast<Module*>(_instance())->onStartUp();
}

template<class SubType, class... Args>
static void
startUp(Args&& ...args) {
  static_assert(std::is_base_of<T, SubType>::value,
                "Provided type isnt derivered from type the module is initialized with");

  if (isStartedUp()) {
    std::cerr << "Trying to acces an already started module" << std::endl;
  }

  _instance() = new SubType(std::forward<Args>(args)...);
  isStartedUp() = true;

  static_cast<Module*> (_instance())->onStartUp();
}

/*
* @brief
*  Shuts down this module and releases any resources it was using.
* @param NONE
* @return NONE
*/
static void
shutDown() {
  if (isDestroyed()) {
    std::cerr << "trying to shut down an already shut down module" << std::endl;
  }

  if (!isStartedUp * ()) {
    std::cerr << "Trying to shut down a module that was never staretd" << std::endl;
  }

  static_cast<Module*>(_instance())->onShutDown();

  delete (_isntance());
  isDestroyed() = true;
}

/*
* @brief
*  Query if the module has been started
* @param NONE
* @return NONE
*/
static bool
isStarted() {
  return isStartedUp() && !isDestroyed();
}

protected:

  /*
  * @brief
  *  Default constructor.
  */
  Module() = default;

  /*
  * @brief
  *  Default destructor.
  */
  ~Module() = default;

  Module(Module&&) = delete;

  Module(const Module&) = delete;

  Module&
  operator= (Module&&) = delete;

  Module&
  operator(const Module& ) = delete;

  virtual void
  onStartUp(){}

  virtual void
  onShutDown(){}

  /*
  * @brief
  *  Creates a singleton instance of this module.
  *  Throws an exception if the module was not initialized.
  * @param NONE
  * @return T*&
  */
  static T*&
  _isntance() {
    static T* inst = nullptr;
    return inst;
  }

  /*
  * @brief
  *  Checks if the module has been shut down.
  *  If the module was never started this will return false.
  * @param NONE
  * @return 
  */
  static bool&
  isDestroyed() {
    static bool inst = false;
    return inst;
  }

  /*
  * @brief 
  *  Checks if the module has been started up
  * @param NONE
  * @return BOOL
  *  Returns false as a default value.s
  */
  static bool&
  isStartedUp() {
    static bool inst = false;
    return inst;
  }
}
