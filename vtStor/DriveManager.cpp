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
#include "DriveManager.h"

#include "StorageUtility.h"

namespace vtStor
{
    std::unique_ptr<cDriveManager> cDriveManager::s_Instance = nullptr;

cDriveManager::cDriveManager()
{

}

cDriveManager::~cDriveManager()
{
    m_DriveEnumerators.clear();
    m_Drives.clear();
}

void cDriveManager::GetInstance(std::unique_ptr<cDriveManagerInterface>& DriveManager)
{
    if (nullptr == s_Instance)
    {
        s_Instance = std::unique_ptr<cDriveManager>(new cDriveManager());
    }
    DriveManager = std::move(s_Instance);
}

void cDriveManager::RegisterDriveEnumerator( std::shared_ptr<cDriveEnumeratorInterface> DriveEnumerator )
{
    m_DriveEnumerators.push_back( DriveEnumerator );
}

eErrorCode cDriveManager::EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges )
{
    eErrorCode error = eErrorCode::None;

    if ( eScanForHardwareChanges::Yes == ScanForHardwareChanges )
    {
        // scan for hardware changes
        m_Drives.clear();
        m_DevicePaths.clear();
    }
    vtStor::GetStorageDevicePaths(m_DevicePaths, eOnErrorBehavior::Continue);

    U32 count = 0;

    for (const auto& devicePath : m_DevicePaths)
    {
        for (auto& enumerator : m_DriveEnumerators)
        {
            error = enumerator->EnumerateDrive(devicePath, m_Drives, count);
            if (1 == count)
            {
                break;
            }      
        }
    }    

    return( error );
}

const Vector_Drives& cDriveManager::GetDrives()
{
    return( m_Drives );
}

std::shared_ptr<cDriveInterface> cDriveManager::GetDrive(const U32 DriveIndex)
{
    std::shared_ptr<cDriveInterface> driveInterface = nullptr;
    if (m_Drives.size() > DriveIndex)
    {
        driveInterface = m_Drives[DriveIndex];
    }
    return(driveInterface);
}

}