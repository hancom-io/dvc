﻿/*
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
#include "Factory.h"

#include "Source\DVCOutputJson.h"

IDVCOutput* Factory::getOutput(OutputType type)
{
    if (type == OutputType::JSON) {
        return new DVCOutputJson();
    }

    return NULL;
}

bool Factory::deleteObject(IDVCOutput* output)
{
    if (output == NULL) {
        return false;
    }

    if (output->getType() == OutputType::JSON) {
        delete static_cast<DVCOutputJson*>(output);
        return true;
    }

    delete output;

    return true;
}