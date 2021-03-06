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

#include <memory>

#include <Windows.h>
#include <Ntddscsi.h>

#include "ErrorCodes.h"
#include "IBuffer.h"
#include "IProtocol.h"

#include "StorageUtility/Scsi.h"

namespace vtStor
{
namespace Protocol
{

class VT_STOR_SCSI_PROTOCOL_API cScsiPassThrough : public IProtocol
{
public:
    virtual eErrorCode IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> Essense, std::shared_ptr<IBuffer> DataBuffer) override;
    
private:
    void InitializePassThroughDirect(
        const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics,
        const StorageUtility::Scsi::uCdb& CdbRegister,
        std::shared_ptr<IBuffer> DataBuffer,
        U32 TimeoutValueInSeconds
        );

    //! Initialize the iCurrentTaskFile. and the PreviousTaskFile in the ATA_PASS_THROUGH_DIRECT structure
    //!
    void InitializeCdbRegister( const StorageUtility::Scsi::uCdb& ScsiCommandField );

    eErrorCode IssuePassThroughDirectCommand( const DeviceHandle& Handle, U32& BytesReturned );

private:
    SCSI_PASS_THROUGH_DIRECT m_ScsiPassThrough;
};

}
}
