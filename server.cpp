ReadBytes(uint16_t fd, char* buffer, unsigned int count)
{
    // TODO: Complete
    int bytesRead = 0;
    //read returns number of bytes read
    bytesRead = read(fd, buffer, count);
    return bytesRead;
}

//A function that takes data and a number x and writes x bytes of data to the socket/sends it
int WriteBytes(uint16_t someSocket, const char *data, int x) {
    int bytesSent;
    bytesSent = send(someSocket, data, x, 0);
    return bytesSent;
}