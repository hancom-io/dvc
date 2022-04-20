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

#include "pch.h"
#include "ReaderUtil.h"

#include <codecvt>

OWPML::CObject* ReaderUtil::FindObject(OWPML::CObject* object, UINT refID)
{
    OWPML::Objectlist* list = object->GetObjectList();

    if (!list)
        return NULL;

    size_t nCnt = list->size();
    nCnt;

    OWPML::CObject* obj = NULL;
    OWPML::CObject* resultObj = NULL;
    size_t i = 0;
    for (i = 0; i < nCnt; i++)
    {
        obj = list->at(i);

        if (obj) {
            if (refID != obj->GetID()) {
                resultObj = FindObject(obj, refID);
                if (resultObj)
                    return resultObj;
            }
            else
            {
                return obj;
            }
        }
    }

    return NULL;
}

OWPML::CObject* ReaderUtil::FindObjectFromParents(OWPML::CObject* object, UINT refID, bool findToFirst)
{
    if (!object)
        return NULL;

    if (object->GetParentObj() && object->GetParentObj()->GetID() == refID)
        return object->GetParentObj();
    else if (!object->GetParentObj() && findToFirst)
        return FindObject(object, refID);
    else
        return FindObjectFromParents(object->GetParentObj(), refID, findToFirst);

    return NULL;
}

bool ReaderUtil::FindObjectAndSaveObj(OWPML::CObject* object, UINT refID, std::vector<OWPML::CObject*>& vecObj)
{
    OWPML::Objectlist* list = object->GetObjectList();

    if (!list)
        return NULL;

    size_t nCnt = list->size();
    nCnt;

    OWPML::CObject* obj = NULL;
    OWPML::CObject* resultObj = NULL;
    size_t i = 0;
    for (i = 0; i < nCnt; i++)
    {
        obj = list->at(i);

        if (obj) {
            if (refID != obj->GetID()) {
                FindObjectAndSaveObj(obj, refID, vecObj);                
            }
            else {
                vecObj.push_back(obj);
                FindObjectAndSaveObj(obj, refID, vecObj);
            }
        }
    }

    return false;
}

std::wstring ReaderUtil::s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> convertX;
    return convertX.from_bytes(str);
}

std::string ReaderUtil::ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> convertX;
    return convertX.to_bytes(wstr);
}

bool ReaderUtil::findInVector(std::vector<UINT> obj, UINT value)
{
    std::vector<UINT>::iterator iter = obj.begin();

    for (iter; iter != obj.end(); iter++)
    {
        if ((*iter) == value)
            return true;
    }

    return false;
}
