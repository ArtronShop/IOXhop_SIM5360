/* File              : SIM5360_HTTP.h
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_HTTP_H__
#define SIM5360_HTTP_H__

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SIM5360.h"

#define HTTP_ROSPONSE_HEADER_MAX_LENGHT 10

class SIM5360_HTTP {
  public:
	SIM5360_HTTP(SIM5360* obj) : MainObj(obj) { }

	// Request
	bool GET(String url) ;
    bool POST(String url, String data) ;
    bool PUT(String url, String data) ;
	bool sendRequest(String method, String url, String data = "") ;
	
	void addHeader(String name, String value) ;
	void setTimeout(int timeout) ;
	
	// Response
	float http_version = 1.1;
	
	int http_code() ;
	String content() ;
	int length() ;
	
	int header() ;
	String header(String name) ;
	String headerName(int index) ;
	String headerVaule(int index) ;

  private:
	SIM5360* MainObj;
	
	bool isHTTPS = false;
	
	// Request
    String _http_req_header;
	int _timeout = 30000;
	
	bool connectTo(String host, int port) ;
	
	// Response
	int _http_ros_code = 0;
	String _http_ros_content;
	int _http_ros_content_length;
	String _http_ros_header[HTTP_ROSPONSE_HEADER_MAX_LENGHT];
	int _http_ros_header_length;

}
;

#endif