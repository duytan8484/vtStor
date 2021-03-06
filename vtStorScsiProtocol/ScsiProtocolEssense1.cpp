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

#include "ScsiProtocolEssense1.h"
#include "StorageUtility.h"

namespace vtStor
{
namespace Protocol
{
const size_t cEssenseScsi1::COMMAND_CHARACTERISTICS_OFFSET   = cProtocolEssense::DATA_OFFSET;
const size_t cEssenseScsi1::TASKFILE_REGISTER_OFFSET = cEssenseScsi1::COMMAND_CHARACTERISTICS_OFFSET + sizeof(StorageUtility::Scsi::sCommandCharacteristics);

const size_t cEssenseScsi1::SIZE_IN_BYTES = cEssenseScsi1::COMMAND_CHARACTERISTICS_OFFSET
                            + sizeof(StorageUtility::Scsi::sCommandCharacteristics)
                            + sizeof(StorageUtility::Scsi::uCdb);

UUID cEssenseScsi1::FormatType;

cEssenseScsi1 cEssenseScsi1::Reader(std::shared_ptr<const IBuffer> Buffer)
{
    return(cEssenseScsi1(Buffer));
}

cEssenseScsi1 cEssenseScsi1::Writer(std::shared_ptr<IBuffer> Buffer)
{
    CreateUUID(FormatType);
    return(cEssenseScsi1(Buffer, FormatType));
}

cEssenseScsi1::cEssenseScsi1(std::shared_ptr<IBuffer> Buffer) :
cProtocolEssense(Buffer)
{
}

cEssenseScsi1::cEssenseScsi1(std::shared_ptr<IBuffer> Buffer, const UUID& Format) :
cProtocolEssense(Buffer, Format)
{
}

cEssenseScsi1::cEssenseScsi1(std::shared_ptr<const IBuffer> Buffer) :
cProtocolEssense(Buffer)
{
}

StorageUtility::Scsi::sCommandCharacteristics& cEssenseScsi1::GetCommandCharacteristics()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::sCommandCharacteristics&)buffer[COMMAND_CHARACTERISTICS_OFFSET]);

}

const StorageUtility::Scsi::sCommandCharacteristics& cEssenseScsi1::GetCommandCharacteristics() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::sCommandCharacteristics&)buffer[COMMAND_CHARACTERISTICS_OFFSET]);
}

StorageUtility::Scsi::uCdb& cEssenseScsi1::GetCdbRegisters()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::uCdb&)buffer[TASKFILE_REGISTER_OFFSET]);
}

const StorageUtility::Scsi::uCdb& cEssenseScsi1::GetCdbRegisters() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::uCdb&)buffer[TASKFILE_REGISTER_OFFSET]);
}
}
}
