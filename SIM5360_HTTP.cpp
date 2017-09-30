/* File              : SIM5360_HTTP.cpp
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_HTTP_CPP__
#define SIM5360_HTTP_CPP__

#include "SIM5360_HTTP.h"

bool SIM5360_HTTP::GET(String url) {
	return sendRequest("GET", url);
}

bool SIM5360_HTTP::POST(String url, String data) {
	return sendRequest("POST", url, data);
}

bool SIM5360_HTTP::PUT(String url, String data) {
	return sendRequest("PUT", url, data);
}

bool SIM5360_HTTP::sendRequest(String method, String url, String data = "") {
	if (url.substring(0, 8) != "https://" && url.substring(0, 7) != "http://") {
		MainObj->_error_msg = "support http or https only";
		return false;
	}
	isHTTPS = url.substring(0, url.indexOf(":")) == "https";
	
	String host;
	int port;
	
	int endHostPort = url.indexOf("/", isHTTPS ? 8 : 7);
	if (endHostPort < 0) endHostPort = url.length();
	int startPort = url.indexOf(":", isHTTPS ? 8 : 7);
	if (startPort > 0 && endHostPort > 0) {
		host = url.substring(isHTTPS ? 8 : 7, startPort);
		port = url.substring(startPort+1, endHostPort).toInt();
	} else if (startPort < 0 && endHostPort > 0) {
		host = url.substring(isHTTPS ? 8 : 7, endHostPort);
		port = isHTTPS ? 443 : 80;
	} else
		return false;
	
	String path = url.substring(endHostPort);
	path = (path == "") ? "/" : path;
	/*
	Serial.println("Host: " + host);
	Serial.println("Port: " + String(port));
	Serial.println("Url: " + path);
	*/
	
	if (isHTTPS) {
		MainObj->SendCMD("AT+CHTTPSSTART");
		String ros = MainObj->readString(0, 3000, "\r\nOK\r\n");
		if (ros.indexOf("\r\nOK\r\n") < 0 && ros.indexOf("\r\nERROR\r\n") < 0) {
			MainObj->_error_msg = "Error! : " + ros;
			return false;
		}
	}
	
	if (!connectTo(host, port)) {
		MainObj->_error_msg = "Can't open connect";
		return false;
	}
	
	// Serial.println("Connect work !");
	
	String http_request = "";
	http_request += method + " " + path + " HTTP/1.1\r\n";
	http_request += "Host: " + host + "\r\n";
	if (_http_req_header.indexOf("") < 0) 
		http_request += "User-Agent: SIM5360 dev by IOXhop\r\n";
	http_request += _http_req_header;
	if (_http_req_header.indexOf("Content-Type:") < 0 && data.length() > 0)
		http_request += "Content-Type: application/x-www-form-urlencoded\r\n";
	if (data.length() > 0)
		http_request += (String)"Content-Length: " + data.length() + "\r\n";
	http_request += "\r\n"; // END of request
	if (data.length() > 0) http_request += data; // Add data after end request
	/*
	Serial.println("---------------------");
	Serial.print(http_request);
	Serial.println("---------------------");
	*/
	if (isHTTPS) {
		MainObj->SendCMD("AT+CHTTPSSEND=" + String(http_request.length()));
	}
	
	MainObj->GSMSerial->print(http_request);
	if (!isHTTPS) MainObj->GSMSerial->write(CTRL_Z);
	
	if (isHTTPS) {
		if (!MainObj->readString(0, _timeout, "RECV EVENT")) {
			MainObj->_error_msg = "Send https header fail";
			return false;
		}
		MainObj->SendCMD("AT+CHTTPSRECV=1024");
	} else {
		if (!MainObj->findOK(5000)) {
			MainObj->_error_msg = "Send http header fail";
			return false;
		}
	}
	if (!MainObj->readString(0, isHTTPS ? 1000 : _timeout, isHTTPS ? "+CHTTPSRECV: " : "+CHTTPACT: ")) {
		MainObj->_error_msg = "Timeout of " + String(_timeout / 1000) + "s";
		return false;
	}
	String code = MainObj->readString(5, 100);
	// Serial.println("Code: " + code);
	if (code != "DATA,") {
		MainObj->_error_msg = "Error code: " + code;
		return false;
	}
	int http_response_length = MainObj->readString(0, 100, "\r\n").toInt();
	String http_response = MainObj->readString(http_response_length, 10000);
	
	int end_of_header = http_response.indexOf("\r\n\r\n");
	String http_response_header = http_response.substring(0, end_of_header);
	int offset = 0, index = 0;
	
	/*Serial.println("---------------------");
	bool isKey = true;
	for (int i=0;i<end_of_header;i++) {
		if (http_response.charAt(i) == '\r') {
			Serial.println(_http_ros_header[index]);
			index++;
			isKey = true;
		} else if (http_response.charAt(i) == '\n') {
			// pass
		} else {
			_http_ros_header[index] += (char)http_response.charAt(i);
		}
	}*/
	// Serial.println("---------------------");
	
	while (1) {
		int end_of_line = http_response_header.indexOf("\r\n", offset);
		if (end_of_line < 0) break;
		String line = http_response.substring(offset, end_of_line);
		if (offset == 0) {
			int verEndPos = line.indexOf(" ");
			http_version = line.substring(line.indexOf("/") + 1, verEndPos).toFloat();
			_http_ros_code = line.substring(verEndPos + 1, line.indexOf(" ", verEndPos + 1)).toInt();
		} else {
			_http_ros_header[index++] = line;
		}
		offset = end_of_line + 2;
	}
	
	_http_ros_header_length = index;
	
	_http_ros_content = http_response.substring(end_of_header + 4);
	_http_ros_content_length = _http_ros_content.length();
	
	if (isHTTPS) {
		MainObj->SendCMD("AT+CHTTPSCLSE");
		if (!MainObj->findOK(5000)) {
			Serial.println("Warning: Close https session fail.");
		} else {
			MainObj->SendCMD("AT+CHTTPSSTOP");
			if (!MainObj->findOK()) {
				Serial.println("Warning: Close https session fail.");
			}
		}
	}
	
	return true;
}

void SIM5360_HTTP::addHeader(String name, String value) {
	_http_req_header += name + ": " + value;
}

void SIM5360_HTTP::setTimeout(int timeout) {
	_timeout = timeout;
}

int SIM5360_HTTP::http_code() {
	return _http_ros_code;
}

String SIM5360_HTTP::content()  {
	return _http_ros_content;
}

int SIM5360_HTTP::length() {
	return _http_ros_content_length;
}

int SIM5360_HTTP::header() {
	return _http_ros_header_length;
}

String SIM5360_HTTP::header(String name) {
	String headerVaule_tmp = "";
	for (int index=0;index<_http_ros_header_length;index++) {
		if (_http_ros_header[index].indexOf(name) == 0) {
			headerVaule_tmp = _http_ros_header[index].substring(_http_ros_header[index].indexOf(":") + 1);
			break;
		}
	}
	return headerVaule_tmp;
}

String SIM5360_HTTP::headerName(int index) {
	return _http_ros_header[index].substring(0, _http_ros_header[index].indexOf(":"));
}

String SIM5360_HTTP::headerVaule(int index) {
	return _http_ros_header[index].substring(_http_ros_header[index].indexOf(":") + 1);
}

bool SIM5360_HTTP::connectTo(String host, int port) {
	if (!MainObj->SendCMD("AT+CHTTP" + (String)(isHTTPS ? "SOPSE" : "ACT") + "=\"" + host + "\"," + String(port))) return false;
	if (isHTTPS) {
		return MainObj->findOK(5000);
	} else {
		String ros = MainObj->readString(0, 5000, "REQUEST");
		// Serial.println("Rever: " + ros);
		return ros.indexOf("REQUEST") >= 0;
	}
}

#endif