using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    public static class AsyncAwaitTasks
    {

        public static void run(List<string> urls)
        {
            var tasks = urls.Select((url, index) =>
            {
                var socketHandler = ExtendedSocket.Create(url, "/", index);
                return Task.Run(async () => await StartAsync(socketHandler));
            }).ToList();

            Task.WhenAll(tasks).Wait();
        }

        private static async Task StartAsync(ExtendedSocket socket)
        {
            Console.WriteLine($"Starting connection to {socket.Host} {socket.Path}");
            await socket.BeginConnectAsync();
            await HandleConnectAsync(socket);
        }

        private static async Task HandleConnectAsync(ExtendedSocket socket)
        {
            Console.WriteLine($"Id: {socket.Id} connected to {socket.Host} {socket.Path}");
            await socket.BeginSendAsync();
            await HandleSentAsync(socket);
        }

        private static async Task HandleSentAsync(ExtendedSocket socket)
        {
            Console.WriteLine($"Sent data for {socket.Host}");
            await socket.BeginReceiveAsync();
            HandleReceive(socket);
        }

        private static void HandleReceive(ExtendedSocket socket)
        {
            Console.WriteLine($"Callback-{socket.Id}: Received response from {socket.Host} ({socket.Path}) with header {socket.OnlyHeader}\nContent length: {socket.ContentLength}\n");
            socket.ShutdownAndClose();
        }
    }
}
