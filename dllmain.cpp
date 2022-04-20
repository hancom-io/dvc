/*
 * Copyright 2022 Hancom Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 // dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

#include "../../export/export.h"
#include "../../export/ExportInterface.h"

#include <iostream>

#include "Source\DVCModule.h"

namespace DVC {

    IDVC* createDVC(/*std::wstring dvcFile, std::wstring hwpxFile, bool printOutput*/)
    {
        DVCModule* pDVCModule = new DVCModule(/*dvcFile.c_str(), hwpxFile.c_str(), printOutput*/);
        return pDVCModule;
    }

    void deleteDVC(IDVC* object)
    {
        if (object != NULL) {
            DVCModule* pDVCModule = static_cast<DVCModule*>(object);
            delete pDVCModule;
            object = NULL;
        }
    }
}
#ifdef WINDOWS
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#endif