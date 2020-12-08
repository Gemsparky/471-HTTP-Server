//object to store data received from socket and how many bytes were received
struct DataBytes{
    int bytes;
    char *data;
};

//A function that reads from the socket, and return both the data and the number of bytes read
DataBytes ReadBytes(uint16_t someSocket){
    //create DataBytes object to return at the end
    DataBytes result;
    //store bytes and data received from reading the socket in DataBytes object attributes respectively
    result.bytes = read(someSocket, result.data, 4096, 0);

    if (results.bytes < 0){
        cerr<<"Error in receiving HTTP request"<<endl;
        return DataBytes temp = {0, ""};
    }
    else (results.bytes > 0){
        return result;
    }
}

//A function that takes data and a number x and writes x bytes of data to the socket/sends it
int WriteBytes(uint16_t someSocket, char *data, int x) {
    int bytesSent;
    bytesSent = send(someSocket, data, x, 0);
    return bytesSent;
}