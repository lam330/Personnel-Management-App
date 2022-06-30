# Python 3 server example
from http.server import BaseHTTPRequestHandler, HTTPServer
import time
import requests


hostName = "localhost"
serverPort = 8080

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        print("new req 111")
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()


        # Read file
        f = open("jsonformatter.txt", "r")
        # print(f.read())
        # Post data
        data = f.read()
        # print(data)

        print ("new req 222")
        self.wfile.write(bytes(data, "utf-8"))
        # self.wfile.write(bytes("<var>"data"</var>" , "utf-8"))

        # self.wfile.write(bytes("</body></html>", "utf-8"))

        print("new req 333")

if __name__ == "__main__":
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    # Read file
    f = open("jsonformatter.txt", "r")
    print(f.read())
    try:
        webServer.serve_forever()

    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")