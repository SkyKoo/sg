/*
Copyright 2013, Sky Gu. All rights reserved.
*
* * Licensed under the GNU LESSER GENERAL PUBLIC LICENSE(the "License");
* * you may not use this file except in compliance with the License.
* * You may obtain a copy of the License at
* *
* * http://www.gnu.org/licenses/lgpl.html
* *
* * Unless required by applicable law or agreed to in writing, software
* * distributed under the License is distributed on an "AS IS" BASIS,
* * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* * See the License for the specific language governing permissions and
* * limitations under the License.
* */

//// Author: Sky Gu (skylove_gcm@hotmail.com)
//////

#include "sgConfig.h"
#include "sgTypeCast.h"

namespace sg
{

SGConfig::SGConfig(const std::string &configFile)
{
    _file = configFile;
    std::ifstream file(configFile.c_str());
    std::string line;
    std::string name;
    std::string value;
    size_t posEqual;
    while (std::getline(file, line))
    {
        if (!line.length()) continue;
        if (line[0] == '#') continue;
        if (line[0] == ';') continue;

        posEqual = line.find('=');
        name = line.substr(0, posEqual);
        value = line.substr(posEqual + 1);
        size_t index = value.find('\r');

        if (index != std::string::npos)
            value = value.substr(0, index);

        index = value.find('\n');
        if (index != std::string::npos)
            value = value.substr(0, index);

        name = upperCase(name);
        _mapContent[name] = value;
    }

    _fileNotExisted = _mapContent.empty();
    file.close();
}

SGConfig::~SGConfig(void)
{
    _mapContent.clear();
}

std::string SGConfig::upperCase(const std::string &input)
{
    std::string output(input);
    for (unsigned int i = 0; i < output.size(); i++)
    {
        if (output[i] >= 97 && output[i] <= 122)
        {
            output[i] -= 32;
        }
    }
    return output;
}

void SGConfig::getValue(const std::string &entry, std::string &output)
{
    std::string upEntry = upperCase(entry);
    MapContent::const_iterator ci = _mapContent.find(upEntry);
    if (ci != _mapContent.end())
    {
        output = ci->second;
    }
    else
    {
        output = "";
    }
}

void SGConfig::getValue(const std::string &entry, int &output)
{
    std::string upEntry = upperCase(entry);
    MapContent::const_iterator ci = _mapContent.find(upEntry);
    if (ci != _mapContent.end())
    {
        SGTypeCast::toInt(output, ci->second);
    }
    else
    {
        output = 0;
    }
}

void SGConfig::setValue(const std::string &entry, const std::string &value)
{
    std::string upEntry = upperCase(entry);
    MapContent::iterator it = _mapContent.find(upEntry);
    if (it != _mapContent.end())
    {
        it->second = value;
    }
    else
    {
        _mapContent[upEntry] = value;
    }
}

void SGConfig::save()
{
    std::ofstream outFile(_file.c_str());
    MapContent::iterator it = _mapContent.begin();
    while (it != _mapContent.end())
    {
        std::string value = it->first + "=" + it->second;
        outFile << value << std::endl;
        ++it;
    }
    outFile.close();
}

} // namespace sg
