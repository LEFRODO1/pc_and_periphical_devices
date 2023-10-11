using System.IO.Pipes;
using System.Runtime.CompilerServices;

public struct Data
{
    public int number;
    public int age;
}

class PipeServer
{
    static void Main()
    {
        using NamedPipeServerStream pipeServer = new("channel", PipeDirection.InOut);
        Console.WriteLine("Waiting for client connection...");
        pipeServer.WaitForConnection();
        Console.WriteLine("Client connected");
        
        Data data = new Data();
        Console.Write("Введите число: ");
        data.number = int.TryParse(Console.ReadLine(), out int num) ? num : 0;
        //int number_r = int.Parse(Console.ReadLine());
        Console.Write("Введите возраст: ");
        data.age = int.TryParse(Console.ReadLine(), out int aue) ? aue : 0;
        //int age_r = int.Parse(Console.ReadLine());
      

        byte[] bytes = new byte[Unsafe.SizeOf<Data>()];
        Unsafe.As<byte, Data>(ref bytes[0]) = data;
        pipeServer.Write(bytes);
        //sw.BaseStream.Write(bytes, 0, bytes.Length);

        byte[] received_bytes = new byte[Unsafe.SizeOf<Data>()];
        pipeServer.Write(received_bytes);
        //sw.BaseStream.Read(received_bytes, 0, received_bytes.Length);
        Data received_data = Unsafe.As<byte, Data>(ref received_bytes[0]);
        Console.WriteLine($"Received data: number = {received_data.number}, age = {received_data.age}");
    }
}