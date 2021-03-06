/*
<License>
Copyright 2016 Virtium Technology

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

#ifndef __vtStorDriveScsiCommandExtensionManaged_h__
#define __vtStorDriveScsiCommandExtensionManaged_h__
#pragma once

#include "IScsiCommandExtensions.h"
#include "UniquePtrManaged.h"

namespace vtStor
{
    namespace Scsi
    {
        namespace Managed
        {
            public ref class cScsiCommandExtensions
            {
            public:
                cScsiCommandExtensions(vtStor::Managed::IRunTimeDll^ RunTimeDll);

            protected:
                ~cScsiCommandExtensions();

            protected:
                !cScsiCommandExtensions();

            public:
                vtStor::Managed::eErrorCode IssueCommand_AtaIdentifyDevice(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data);
                vtStor::Managed::eErrorCode IssueCommand_AtaReadDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count);
                vtStor::Managed::eErrorCode IssueCommand_AtaWriteDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count);
                vtStor::Managed::eErrorCode IssueCommand_AtaReadBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data);
                vtStor::Managed::eErrorCode IssueCommand_AtaWriteBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data);
                vtStor::Managed::eErrorCode IssueCommand_AtaSmart(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand);

            private:
                vtStor::Managed::cUniquePtr<vtStor::IScsiCommandExtensions> m_ScsiCommandExtensions;
            };
        }
    }
}

#endif