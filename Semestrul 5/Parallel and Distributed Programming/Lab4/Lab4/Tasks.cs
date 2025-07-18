

namespace Lab4
{
    public static class Tasks
    {
        public static void run(List<string> urls)
        {
            var tasks = urls.Select((url, index) =>
            {
                var socketHandler = ExtendedSocket.Create(url, "/", index);
                return Task.Run(() => Start(socketHandler));
            }).ToList();

            Task.WhenAll(tasks).Wait();
        }

        private static Task Start(ExtendedSocket socket)
        {
            Console.WriteLine($"Starting connection to {socket.Host} {socket.Path}");
            return socket.BeginConnectAsync().ContinueWith(t => HandleConnect(socket));
        }

        private static Task HandleConnect(ExtendedSocket socket)
        {
            Console.WriteLine($"Id: {socket.Id} connected to {socket.Host} {socket.Path}");
            return socket.BeginSendAsync().ContinueWith(t => HandleSent(socket));
        }

        private static Task HandleSent(ExtendedSocket socket)
        {
            Console.WriteLine($"Sent data for {socket.Host}");
            return socket.BeginReceiveAsync().ContinueWith(t => HandleReceive(socket));
        }

        private static void HandleReceive(ExtendedSocket socket)
        {
            Console.WriteLine($"Callback-{socket.Id}: Received response from {socket.Host} ({socket.Path}) with header {socket.OnlyHeader}\nContent length: {socket.ContentLength}\n");
            socket.ShutdownAndClose();
        }
    }
}