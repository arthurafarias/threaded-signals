/***********************************************************************************************************************
*                                                                                                                      *
* Threaded Signals Example v0.1                                                                                                      *
*                                                                                                                      *
* Copyright (c) 2015-(today) Arthur de A. Farias                                                                       *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file main.cpp
	@author Arthur de A. Farias <arthur@afarias.org>
	@brief Program Entry Point
 */


#include <string>
#include <iostream>

#include <signal.hpp>

struct example : std::enable_shared_from_this<example>
{
    signal<std::shared_ptr<example>, std::string> on_data_received;
};

int main(int argc, char* argv[])
{
    /**
     * 
     */
    std::promise<std::string> p;
    auto f = p.get_future();

    auto object = std::make_shared<example>();

    object->on_data_received += [&p](std::shared_ptr<example> sender, std::string data){
        std::cout << data << std::endl;
        p.set_value(data);
    };

    object->on_data_received(object, "Hello World");

    f.wait();
    auto result = f.get();

    if (result == "Hello World") {
        std::cout << "Success" << std::endl;
    }

    return 0;
}