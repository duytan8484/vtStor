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
#ifndef __vtStorScsiCommandDescriptor_h__
#define __vtStorScsiCommandDescriptor_h__

#include <memory>

#include "IBuffer.h"
#include "CommandDescriptor.h"
#include "Scsi.h"

namespace vtStor
{
namespace Scsi
{

const size_t COMMAND_DESCRIPTOR_VERSION_OFFSET = 0;
const size_t COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES = 2;
const size_t COMMAND_DESCRIPTOR_RESERVED0_OFFSET = COMMAND_DESCRIPTOR_VERSION_OFFSET + COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES;
const size_t COMMAND_DESCRIPTOR_RESERVED0_SIZE_IN_BYTES = 2;

class VT_STOR_SCSI_API cCommandDescriptorScsi : public cCommandDescriptor
{
public:
    static const size_t SIZE_IN_BYTES;
    static UUID FormatType;

public:
    static cCommandDescriptorScsi Reader(std::shared_ptr<const IBuffer> Buffer);
    static cCommandDescriptorScsi Writer(std::shared_ptr<IBuffer> Buffer);
    static cCommandDescriptorScsi Modifier(std::shared_ptr<IBuffer> Buffer);

protected:
    cCommandDescriptorScsi(std::shared_ptr<IBuffer> Buffer);
    cCommandDescriptorScsi(std::shared_ptr<IBuffer> Buffer, const UUID& Format);
    cCommandDescriptorScsi(std::shared_ptr<const IBuffer> Buffer);

public:
    StorageUtility::Scsi::uCommandInputFields& GetCommandInputFields();
    const StorageUtility::Scsi::uCommandInputFields& GetCommandInputFields() const;
    StorageUtility::Scsi::sCommandCharacteristics& GetCommandCharacteristics();
    const StorageUtility::Scsi::sCommandCharacteristics& GetCommandCharacteristics() const;

private:
    static const size_t CDB_FIELDS_OFFSET;
    static const size_t COMMAND_CHARACTERISTICS_OFFSET;
};

}
}

#endif
