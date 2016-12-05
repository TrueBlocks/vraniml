//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "..\Utility.h"

#if 0
#include "Windows.h"
#include "WinInet.h"

#include "stdio.h"

SFString UrlDump(HINTERNET hInternet, char *url);
SFString Error(SFInt32 dError, const SFString& caller);

SFString vrCacheFile(SFString& remoteFilename, SFInt32 mode)
{
	char buff[1024];
	DWORD size = 1024;
	if (remoteFilename.Find("://")==-1)
	{
		SFString baseURL = "";
		if (!InternetCombineUrl((char*)baseURL, (char*)remoteFilename, buff, &size, 0))
			return Error(GetLastError(), "vrCacheFile");
	} else
	{
		if (!InternetCanonicalizeUrl((char*)remoteFilename, buff, &size, 0))
		{
			return Error(GetLastError(), "vrCacheFile");
		}
	}
	
	URL_COMPONENTS components;
	memset(&components, 0, sizeof(URL_COMPONENTS));
	components.dwStructSize      = sizeof(URL_COMPONENTS);
  components.dwSchemeLength    = TRUE;
  components.dwHostNameLength  = TRUE;
  components.dwUserNameLength  = TRUE;
  components.dwPasswordLength  = TRUE;
  components.dwUrlPathLength   = TRUE;
  components.dwExtraInfoLength = TRUE;

	if (!InternetCrackUrl(buff, 0, 0, &components))
		return Error(GetLastError(), "vrCacheFile");

	if (SFString(components.lpszScheme).Left(4)=="file")
	{
		SFString ret = components.lpszUrlPath;
		ret.ReplaceAll("%20", " ");
		return ret;
	}

	// Only need one
	static HINTERNET hInternet = NULL;
	if (!hInternet)
		hInternet = InternetOpen("VRaniML SDK", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, FALSE);
	
	if (hInternet)
	{
/*
		DWORD result;
		if (!InternetGetConnectedState(&result, NULL))
		{
			AfxMessageBox("Please connect to the internet first");
		}
		if (result & INTERNET_CONNECTION_MODEM)
		{
			AfxMessageBox("Local system uses a modem to connect to the Internet.");
		}
		if (results & INTERNET_CONNECTION_LAN)
		{
			AfxMessageBox("Local system uses a local area network to connect to the Internet.");
		}
		if (results & INTERNET_CONNECTION_PROXY)
		{
			AfxMessageBox("Local system uses a proxy server to connect to the Internet.");
		}
		if (result & INTERNET_CONNECTION_MODEM_BUSY)
		{
			AfxMessageBox("Local system's modem is busy with a non-Internet connection.");
		}
		
		char host[1024];
		strncpy(host, components.lpszHostName, components.dwHostNameLength);
		char user[1024];
		strncpy(user, components.lpszUserName, components.dwUserNameLength);
		char pass[1024];
		strncpy(pass, components.lpszPassword, components.dwPasswordLength);

		HINTERNET hConnection = InternetConnect(hInternet, 
																							host,
																							components.nPort,
																							user,
																							pass,
																							INTERNET_SERVICE_HTTP,
																							0, 0);
*/
		return UrlDump(hInternet, buff);
	}

	return nullString;
}

SFString UrlDump(HINTERNET hInternet, char *url)
{
	//vrInitiateDownload();

	HINTERNET hUrlDump = InternetOpenUrl(hInternet, url, NULL, NULL, INTERNET_FLAG_RAW_DATA, 0);

  if (!hUrlDump)
		return Error(GetLastError(), "UrlDump");
	
	FILE *out = fopen("temp.fil", "wb");
	if (!out)
		return Error(GetLastError(), "UrlDump");

  unsigned long nBytes=TRUE;
  long bufferSize=8000;
	// Allocate the buffer
  char *lpszData = new char[bufferSize+1];

  // and read till we are done
	do
  {
		// Read the data
    if (!InternetReadFile(hUrlDump,(LPVOID)lpszData,bufferSize,&nBytes))
    {
			Error(GetLastError(),"InternetReadFile");
      break;
    } else
    {
			// Add a null terminator to the end of the buffer
      lpszData[nBytes] = '\0';
      fwrite(lpszData, sizeof(char), nBytes, out);
			//fprintf(out, "%s", lpszData[nBytes]strcat(ret, lpszData);
		  //vrReportProgress();
    }
  } while (nBytes);

  // clean up the buffer
	delete [] lpszData;

  InternetCloseHandle(hUrlDump);

  //vrCompletedDownload();
	if (out)
		fclose(out);
	return "temp.fil";
}

SFString Error(SFInt32 dError, const SFString& caller)
{
	char buff[1000];
	sprintf(buff, "Error: %d --> %s", dError, caller);
	MessageBox(NULL, buff, "Error", MB_OK);
	return nullString;

/*
	TCHAR szTemp[356] = "", *szBuffer=NULL, *szBufferFinal = NULL;
  DWORD  dwIntError , dwLength = 0;
  char strName[256]="";

  FormatMessage(FORMAT_MESSAGE_FROM_HMODULE,
  GetModuleHandle("wininet.dll"),dError,0,(LPSTR)strName,256,NULL);
	wsprintf (szTemp,  "%s error code: %d\nMessage: %s\n", 
	szCallFunc, dError, strName);
  int response;
        
  if (dError == ERROR_INTERNET_EXTENDED_ERROR)
  {
		InternetGetLastResponseInfo (&dwIntError, NULL, &dwLength);
    if (dwLength)
    {
			if ( !(szBuffer = (TCHAR *) LocalAlloc ( LPTR,  dwLength) ) )
      {
				lstrcat (szTemp, TEXT ( "Unable to allocate memory to display Internet error code. Error code: ") );
        lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
        lstrcat (szTemp, TEXT ("\n") );
        response = MessageBox(hErr, (LPSTR)szTemp,"Error",MB_OK);
        return FALSE;
      }
      if (!InternetGetLastResponseInfo (&dwIntError, (LPTSTR) szBuffer, &dwLength))
      {
				lstrcat (szTemp, TEXT ( "Unable to get Internet error. Error code: ") );
        lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
        lstrcat (szTemp, TEXT ("\n") );
        response = MessageBox(hErr, (LPSTR)szTemp,"Error",MB_OK);
        return FALSE;
      }
      if ( !(szBufferFinal = (TCHAR *) LocalAlloc ( LPTR,  (strlen (szBuffer) +strlen (szTemp) + 1)  ) )  )
      {
				lstrcat (szTemp, TEXT ( "Unable to allocate memory. Error code: ") );
        lstrcat (szTemp, TEXT (_itoa (GetLastError(), szBuffer, 10)  ) );
        lstrcat (szTemp, TEXT ("\n") );
        response = MessageBox(hErr, (LPSTR)szTemp,"Error",MB_OK);
        return FALSE;
      }
      lstrcpy (szBufferFinal, szTemp);
      lstrcat (szBufferFinal, szBuffer);
      LocalFree (szBuffer);
      response = MessageBox(hErr, (LPSTR)szBufferFinal,"Error",MB_OK);
      LocalFree (szBufferFinal);
    }
  } else
  {
		response = MessageBox(hErr, (LPSTR)szTemp,"Error",MB_OK);
  }
*/
//  return 0; //response;
}


#else
#include "..\Containers\SFString.h"
#include "WebUtils.h"

#include <winsock.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

SFBool processing_header = 1;
int result_code = -1;

char leftovers[512];    // current header line being read
size_t leftover_size = 0;
char destfilename[] = "\\temp.fil";

//-------------------------------------------------------------------------------------
void do_header_line()
{
	if (leftover_size < sizeof(leftovers))
	{
		// terminate the string for parsing ease
		leftovers[leftover_size] = '\0';
	}

	if (leftover_size == 0)
	{
		// end of the header
		processing_header = 0;

	} else if (result_code == -1)
	{
		int http_rc;
		char * p = leftovers;
		while (! isspace (*p)) p++;
		http_rc  = atoi (p);
		result_code = (http_rc / 100) * 10 + (http_rc % 10);
	}
}

//-------------------------------------------------------------------------------------
void process_data(const char * buffer, size_t bytes, int handle, SFBool binary_file)
{
	while (bytes)
	{
		if (binary_file && ! processing_header)
		{
			if (_write (handle, buffer, bytes) == -1)
			{
				fprintf (stderr, "\nOut of disk space.\n");
				exit (4);
			}
			bytes = 0;  // all bytes processed
		} else
		{
			// Look for an end-of-line indicator
			char * lfptr = (char*) memchr (buffer, '\n', bytes);
			if (lfptr)
			{
				size_t linelen = lfptr - buffer;

				if (processing_header)
				{
					if (linelen + leftover_size >= sizeof(leftovers)-1)
					{
						fprintf (stderr, "Cannot interpret header.\n");
						exit (3);

						if (result_code == 0) 
							result_code = 3;
						processing_header = 0;

					} else
					{
						memcpy (leftovers + leftover_size, buffer, linelen);
						buffer = lfptr + 1;
						bytes -= (linelen + 1);
						leftover_size += linelen;
#ifdef _DEBUG
//						_write (2, leftovers, leftover_size);
//						_write (2, "\n", 2);
#endif
						while (leftover_size && (leftovers [ leftover_size - 1 ] == '\r'))
						{
							leftover_size --;
						}
						do_header_line ();
						leftover_size = 0;
					}

				} else
				{
					// Text line -- a CR is the only thing that might be in leftovers
					size_t bytes_to_write = linelen;

					while (bytes_to_write && buffer [ bytes_to_write - 1 ] == '\r')
					{
						bytes_to_write --;
					}

					if (leftover_size && bytes_to_write)
					{
						// this implies that there was a lone CR -- write it as is
						_write (handle, leftovers, leftover_size);
						leftover_size = 0;
					}

					_write (handle, buffer, bytes_to_write);
					_write (handle, "\r\n", 2);
					leftover_size = 0;
					buffer = lfptr + 1;
					bytes -= (linelen + 1);
				}
			} else
			{
				// partial line
				if (processing_header)
				{
					if (leftover_size + bytes >= sizeof (leftovers))
					{
						fprintf (stderr, "Cannot interpret header.\n");
						if (result_code == 0) 
							result_code = 3;
						processing_header = 0;
					}
				} else
				{
					// text -- write it out -- except trailing CRs
					if (leftover_size)
					{
						// this is queer
						// we have CR (leftover) + string without LF
						for (size_t i = 0; i < bytes; i++)
						{
							if (buffer [ i ] != '\r')
							{
								_write (handle, leftovers, leftover_size);
								leftover_size = 0;
								break;
							}
						}
					}

					if (leftover_size == 0)
					{
						while (bytes && buffer [ bytes - 1 ] == '\r')
						{
							leftover_size = 1;
							leftovers[ 0 ] = '\r';
							bytes --;
						}
						_write (handle, buffer, bytes);
					}
					bytes = 0;
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------
char *GetLocalFile(char *host, char *destination)
{
	if (!_strnicmp("file:", host, 5))
	{
		host += 5;
	}

	if (!memcmp("//", host, 2))
	{
		host += 2;
	}

//	if (host[1] != ':' && (host[0] != '\\' && host[0] != '.'))
//	{
//		char s[256];
//		sprintf(s, ".\\%s", host);
//		strcpy(host, s);
//	}

//	if (CopyFile(host, destination, FALSE))
		return host;
//	else
//		return NULL;
}

SFString vrCacheFile(SFString& remoteFilename, SFInt32 mode)
{
	processing_header = 1;
	leftover_size = 0;
	
	char *source = remoteFilename;
	char *host = source;
	char *destination = destfilename;

	if (!vrIsNetworkFile(host))
	{
		return GetLocalFile(host, destination);
	}
		
	if (!_strnicmp("http:", host, 5))
	{
		host += 5;
	}

	if (!memcmp("//", host, 2))
	{
		host += 2;
	}

	// now we should be pointing to the host name -- we
	// expect a trailing slash after the host name, but 
	// there may not be one if specifying the root (e.g.,
	// "http://www.vsin.com")
	source = strchr(host, '/');
	if (source)
	{
		*(source++) = '\0';
	} else
	{
		source = "";        // empty string, yet not null
	}

	// parse out port number from host specification
	unsigned int port = 80; // default port for HTTP
	char *port_text = strchr (host, ':');
	if (port_text)
	{
		// not using default HTTP port of 80
		*port_text++ = '\0';
		port = atoi (port_text);
		if (port == 0)
		{
			port = 80;  // something's probably wrong
		}
	}

#ifdef _DEBUG
	fprintf (stderr, "I want to get \"/%s\" from port %u of \"%s\" and copy it to ", source, port, host);
	if (destination)
	{
		fprintf (stderr, "\"%s\".\n", destination);
	} else
	{
		fprintf (stderr, "standard output.");
	}
#endif

	WSAData sad_data;
	if (WSAStartup (MAKEWORD (2, 0), &sad_data))
	{
		fprintf (stderr, "Alas, I couldn't start up Windows Sockets.\n");
		return ((char*)NULL);
	}
#ifdef _DEBUG
	fprintf (stderr, "Started up \"%s\" sockets.\n",  sad_data.szDescription); 
#endif

//	atexit(close_winsock);

	struct hostent *servant = gethostbyname (host);
	if (!servant)
	{
		fprintf (stderr, "Could not resolve host named \"%s\".\n", host);
		WSACleanup();
		return ((char*)NULL);
	}

	unsigned char ip_address[16];
	size_t length_of_ip_address = servant->h_length;
	if (length_of_ip_address > sizeof(ip_address))
	{
		fprintf (stderr, "Length of IP address is %u\n", length_of_ip_address);
		WSACleanup();
		return ((char*)NULL);
	}
	memcpy (ip_address, servant->h_addr_list [ 0 ], length_of_ip_address);

#ifdef _DEBUG
	fprintf (stderr, "IP address for %s is %u.%u.%u.%u (len %u)\n", host,
							ip_address[0], ip_address[1], ip_address[2], ip_address[3], length_of_ip_address);
#endif

	// set the socket option so that I can use normal file i/o on it.
	SOCKET my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (my_socket == INVALID_SOCKET)
	{
		fprintf (stderr, "Could not create socket.\n");
		WSACleanup();
		return ((char*)NULL);
	}

	SOCKADDR_IN socket_address;

	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(port);

	if (length_of_ip_address != sizeof(socket_address.sin_addr))
	{
		fprintf (stderr, "Warning:  length of ip address (%u) is not the "
					"same as sizeof(.sin_addr) (%u)\n", 
					length_of_ip_address, sizeof(socket_address.sin_addr));
	}
	memcpy (&socket_address.sin_addr, ip_address, length_of_ip_address);

	if (connect(my_socket, (const sockaddr *) &socket_address, sizeof(socket_address)))
	{
		fprintf (stderr, "Cannot connect to %s\n", host, port);
		WSACleanup();
		closesocket(my_socket);
		return ((char*)NULL);
	}

	fflush (stderr);
	fflush (stdout);

	char buffer [1024];
	int bytes_read;
	int le;
	u_long parameter = 1;

	ioctlsocket (my_socket, FIONBIO, &parameter);

	int option_value = 1;
	if (setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &option_value, sizeof(option_value)))
	{
		fprintf (stderr, "setsockopt call failed.\n");
		WSACleanup();
		closesocket(my_socket);
		return ((char*)NULL);
	}

	bytes_read = sprintf(buffer, "GET /%s HTTP/1.0\r\nUser-Agent:  Webcopy/1.0\r\n\r\n", source);

	send (my_socket, buffer, bytes_read, 0);

	int out_handle;
	if (destination)
	{
		out_handle = _open (destination, _O_CREAT | _O_WRONLY | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE);
		if (out_handle == -1)
		{
			fprintf (stderr, "Could not open \"%s\" as output.\n", destination);
			WSACleanup();
			closesocket(my_socket);
			return ((char*)NULL);
		}
	} else
	{
		out_handle = 1;
	}

	_setmode (out_handle, _O_BINARY);

	do
	{
		bytes_read = recv(my_socket, buffer, sizeof(buffer), 0);

		if (bytes_read == SOCKET_ERROR)
		{
			le = WSAGetLastError ();
		} else if (bytes_read > 0)
		{
			process_data(buffer, bytes_read, out_handle, mode);
		}
	} while (bytes_read);

	closesocket(my_socket);
	WSACleanup();
	if (out_handle!=1)
		_close(out_handle);
	
	return ((result_code == 0 || result_code == 20) ? destination : NULL);
}

#endif
SFBool vrIsNetworkFile(const SFString& host)
{
	return (host.Left(5) == "http:");
}

SFString vrExpandPath(const SFString& str)
{
	if (str[0] == '#')
		return str;
		
	SFString copy = str;
	char *s = copy.GetBuffer();
	if (!vrIsNetworkFile(str) && strncmp(s, "file:", 5))
	{
		// not a fully qualified url, try to see if it's a local file
		char *p = _fullpath(NULL, s, 0);
		SFString ret = p;
		free(p);
		return ret;
	}
	return str;
}

SFBool vrIsValidName(const SFString& name)
{
	if (name.Empty()) 
		return TRUE;
	
	if (name.Find(0x21) != -1)  return FALSE;

	// Invalid character anywhere in name
	if (name.Find('\"') != -1)  return FALSE;
	if (name.Find('\'') != -1)  return FALSE;
	if (name.Find('\\') != -1)  return FALSE;
	if (name.Find('#') != -1)   return FALSE;
	if (name.Find(',') != -1)   return FALSE;
	if (name.Find('.') != -1)   return FALSE;
	if (name.Find('[') != -1)   return FALSE;
	if (name.Find(']') != -1)   return FALSE;
	if (name.Find('{') != -1)   return FALSE;
	if (name.Find('}') != -1)   return FALSE;
		
	// Invalid character in first character of name
	if (name[0] == '0')         return FALSE;
	if (name[0] == '1')         return FALSE;
	if (name[0] == '2')         return FALSE;
	if (name[0] == '3')         return FALSE;
	if (name[0] == '4')         return FALSE;
	if (name[0] == '5')         return FALSE;
	if (name[0] == '6')         return FALSE;
	if (name[0] == '7')         return FALSE;
	if (name[0] == '8')         return FALSE;
	if (name[0] == '9')         return FALSE;
	if (name[0] == '+')         return FALSE;
	if (name[0] == '-')         return FALSE;

	// Reserved keywords
	if (name == "DEF")          return FALSE;
	if (name == "EXTERNPROTO")  return FALSE;
	if (name == "FALSE")        return FALSE;
	if (name == "IS")           return FALSE;
	if (name == "NULL")         return FALSE;
	if (name == "PROTO")        return FALSE;
	if (name == "ROUTE")        return FALSE;
	if (name == "TO")           return FALSE;
	if (name == "TRUE")         return FALSE;
	if (name == "USE")          return FALSE;
	if (name == "eventIn")      return FALSE;
	if (name == "eventOut")     return FALSE;
	if (name == "exposedField") return FALSE;
	if (name == "field")        return FALSE;

	return TRUE;
}
