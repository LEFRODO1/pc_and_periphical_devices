public struct Data
{
    public int number;
    public int age;
}

class PipeClient 
{
    static void Main()
    {
        using NamedPipeClientStream pipeClient = new NamedPipeClientStream(".", "channel", PipeDirection.InOut);
        pipeClient.Connect();
        Console.WriteLine("Client is connected to server");
        byte[] bytes = new byte[Unsafe.SizeOf<Data>()];
        pipeClient.Read(bytes, 0, bytes.Length);
        Data recieved_data = Unsafe.As<byte, Data>(ref bytes[0]);
        Console.WriteLine("Number: " + recieved_data.number);
        Console.WriteLine("Age: " + recieved_data.age);
        recieved_data.number += recieved_data.age;
        byte[] modified_bytes = new byte[Unsafe.SizeOf<Data>()];
        Unsafe.As<byte, Data>(ref modified_bytes[0]) = recieved_data;
        pipeClient.Write( modified_bytes, 0, modified_bytes.Length );   
    }

}