using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.WebSockets;
using System.Reflection.PortableExecutable;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    public static class Callbacks
    {
        public static void run(List<string> urls)
        {
            for (int i = 0; i < urls.Count; i++)
            {
                var socketHandler = ExtendedSocket.Create(urls[i], "/", i);
                Start(socketHandler);
            }
            Thread.Sleep(100000);
        }

        private static void Start(ExtendedSocket socket)
        {
            Console.WriteLine($"Starting connection to {socket.Host} {socket.Path}");
            socket.Start(HandleConnect);
        }

        private static void HandleConnect(ExtendedSocket socket)
        {
            Console.WriteLine($"Id: {socket.Id} connected to {socket.Host} {socket.Path}");
            socket.StartSend(HandleSent);
        }

        private static void HandleSent(ExtendedSocket socket)
        {
            Console.WriteLine($"Sent data for {socket.Host}");
            socket.StartReceive(HandleReceive);
        }

        private static void HandleReceive(ExtendedSocket socket)
        {
            Console.WriteLine($"Callback-{socket.Id}: Received response from {socket.Host} ({socket.Path}) with header {socket.OnlyHeader}\nContent length: {socket.ContentLength}\n");
            socket.ShutdownAndClose();
        }

      
    }
}
