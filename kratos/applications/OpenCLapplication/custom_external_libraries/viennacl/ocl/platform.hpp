#ifndef VIENNACL_OCL_PLATFORM_HPP_
#define VIENNACL_OCL_PLATFORM_HPP_

/* =========================================================================
   Copyright (c) 2010-2012, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                  ViennaCL - The Vienna Computing Library
                            -----------------

   Project Head:    Karl Rupp                   rupp@iue.tuwien.ac.at
               
   (A list of authors and contributors can be found in the PDF manual)

   License:         MIT (X11), see file LICENSE in the base directory
============================================================================= */

/** @file platform.hpp
    @brief Implements a OpenCL platform within ViennaCL
*/

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <vector>
#include "viennacl/ocl/forwards.h"
#include "viennacl/ocl/device.hpp"

namespace viennacl
{
  namespace ocl
  {
    class platform
    {
      
      public:
        platform(std::size_t pf_index = 0)
        {
          cl_int err;
          cl_uint num_platforms;
          cl_platform_id ids[42];   //no more than 42 platforms supported...
          #if defined(VIENNACL_DEBUG_ALL)
          std::cout << "ViennaCL: Getting platform..." << std::endl;
          #endif
          err = clGetPlatformIDs(42, ids, &num_platforms);
          VIENNACL_ERR_CHECK(err);
          assert(num_platforms > pf_index && "ViennaCL: ERROR: Not enough platforms found!");          
          id_ = ids[pf_index];
          assert(num_platforms > 0 && "ViennaCL: ERROR: No platform found!");          
        }
        
        cl_platform_id id() const
        {
          return id_;
        }
        
        /** @brief Returns an information string */
        std::string info() const
        {
          char buffer[1024];
          cl_int err;
          err = clGetPlatformInfo(id_, CL_PLATFORM_VENDOR, 1024 * sizeof(char), buffer, NULL);
          VIENNACL_ERR_CHECK(err);
          
          std::stringstream ss;
          ss << buffer << ": ";

          err = clGetPlatformInfo(id_, CL_PLATFORM_VERSION, 1024 * sizeof(char), buffer, NULL);
          VIENNACL_ERR_CHECK(err);

          ss << buffer;
          
          return ss.str();
        }
        
        //////////////////// get device //////////////////
        /** @brief Returns the available devices of the supplied device type */
        std::vector<device> devices(cl_device_type dtype = CL_DEVICE_TYPE_DEFAULT)
        {
          cl_int err;
          #if defined(VIENNACL_DEBUG_ALL) || defined(VIENNACL_DEBUG_DEVICE)
          std::cout << "ViennaCL: Querying devices available at current platform." << std::endl;
          #endif
          cl_device_id device_ids[VIENNACL_OCL_MAX_DEVICE_NUM];
          cl_uint num_devices;
          err = clGetDeviceIDs(id_, dtype, VIENNACL_OCL_MAX_DEVICE_NUM, device_ids, &num_devices);
          if (err == CL_DEVICE_NOT_FOUND && dtype == CL_DEVICE_TYPE_DEFAULT)
          {
            //workaround for ATI Stream SDK v2.3: No CPUs detected with default device type:
            err = clGetDeviceIDs(id_, CL_DEVICE_TYPE_CPU, VIENNACL_OCL_MAX_DEVICE_NUM, device_ids, &num_devices);
          }
          
          VIENNACL_ERR_CHECK(err);
          #if defined(VIENNACL_DEBUG_ALL) || defined(VIENNACL_DEBUG_DEVICE)
          std::cout << "ViennaCL: Found " << num_devices << " devices." << std::endl;
          #endif
          
          assert(num_devices > 0 && "Error in viennacl::ocl::platform::devices(): No OpenCL devices available!");
          std::vector<device> devices;
          
          for (cl_uint i=0; i<num_devices; ++i)
            devices.push_back(device(device_ids[i]));

          return devices;
        }
        
      private:
        cl_platform_id id_;
    };
    
  }
}

#endif
