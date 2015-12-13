//	Copyright 12-11-2015 Hoenir
//
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.


#include "hssl.h"
// our handy pandy error functions
void
echo_error(const char *message, bool display_errno, int errnoflag)
{
	if(display_errno)
		printf(KBLU "::> "KRED "%s : "RESET "%s.\n" ,message,strerror(errnoflag));
	else
		printf(KBLU "::> "KRED "%s.\n" RESET,message);
}

void
prog_error(const char *message, bool display_errno, int errnoflag)
{
	if(display_errno) {
	    printf(KBLU "::> "KRED "%s : "RESET"%s.\n" ,message,strerror(errnoflag));
		exit(EXIT_FAILURE);
	} else {
		printf(KBLU "::> "KRED "%s.\n" RESET ,message);
		exit(EXIT_FAILURE);
	}
}
