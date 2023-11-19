using System.Net.Http.Json;
using System.Text.Json.Serialization;

namespace TCPServer;

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Newtonsoft.Json;

class TCPServer
{
    private TcpListener tcpListener;
    private Thread listenThread;

    public TCPServer()
    {
        this.tcpListener = new TcpListener(IPAddress.Any, 23);
        this.listenThread = new Thread(new ThreadStart(ListenForClients));
        this.listenThread.Start();
    }
    
    //This is some bullshit written by Walid to wrap the data into JSON - feel free to modify
    public class sensors
    {
        int TankLevel { get; set; }
        private int Moisture { get; set; }
        private int Uv { get; set; }
        private double Humidity { get; set; }
        private double Temperature { get; set; }
    }

    private void ListenForClients()
    {
        this.tcpListener.Start();

        while (true)
        {
            TcpClient client = this.tcpListener.AcceptTcpClient();
            Thread clientThread = new Thread(HandleClientComm);
            clientThread.Start(client);
        }
    }

    private void HandleClientComm(object client)
    {
        TcpClient tcpClient = (TcpClient)client;
        NetworkStream clientStream = tcpClient.GetStream();

        byte[] message = new byte[4096];

        while (true)
        {
            var bytesRead = 0;

            try
            {
                bytesRead = clientStream.Read(message, 0, 4096);
                // Console.WriteLine("bytes read "+ bytesRead);
            }
            catch
            {
                break;
            }

            if (bytesRead == 0)
            {
                break;
            }

            //Printing the data received from the Arduino
            string data = Encoding.ASCII.GetString(message, 0, bytesRead);
            string timestamp = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            Console.WriteLine(timestamp + ", received data: " + data);
            
            //This is not wrapping it properly - feel free to change
            sensors sensors = JsonConvert.DeserializeObject<sensors>(data);
            Console.WriteLine(sensors.ToString());

            //Code for sending responses to the Arduino
            try
            {
                // Example: Send a response back to the client
                Random random = new Random();
                String responseMessage = random.Next(10).ToString(); // Generates 0, 1, 2, 3, 4
                byte[] responseBytes = Encoding.ASCII.GetBytes(responseMessage);
                clientStream.Write(responseBytes, 0, responseBytes.Length);
                clientStream.Flush();
                Console.WriteLine("Data sent to Arduino");
            }
            catch
            {
                Console.WriteLine("Error sending data to Arduino");
                break;
            }
        }

        tcpClient.Close();
    }


    public static void Main()
    {
        TCPServer server = new TCPServer();
        Console.WriteLine("Server started. Listening for incoming connections...");
    }

    
}

