/*
<License>
Copyright 2015 Virtium Technology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
</License>
*/

#ifndef __vtStorBufferInterfaceManaged_h__
#define __vtStorBufferInterfaceManaged_h__
#pragma once

#include "IBuffer.h"
#include "IRunTimeDll.h"
#include "SharedPtrManaged.h"

namespace vtStor
{
    namespace Managed
    {
        public ref class cBufferInterface
        {
        public:
            cBufferInterface( IRunTimeDll^ RunTimeDll, U32 SizeInByte);
            ~cBufferInterface();

        protected:
            !cBufferInterface();

        public:
            operator void*();
            void SetByteAt( U32 Index, U8 value );
            U8 GetByteAt( U32 Index );
            U32 GetSizeInBytes();
            void Memset(U8 Value);

        private:
            cSharedPtr<vtStor::IBuffer> m_Buffer;
        };
    }
}

#endif