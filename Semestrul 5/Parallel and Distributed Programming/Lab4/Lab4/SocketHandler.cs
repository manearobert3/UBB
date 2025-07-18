using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    public class ExtendedSocket : Socket
    {

        public int Id { get; set; }
        public string Host { get; set; }
        public string Path { get; set; }
        private IPEndPoint endPoint { get; set; }
        private byte[] buffer = new byte[8192];
        private StringBuilder headerBuilder = new StringBuilder();
        private int contentLength;
        private int bytesReceived;

        public StringBuilder OnlyHeader { get; private set; }
        public int ContentLength { get => contentLength; }

        public static ExtendedSocket Create(string baseUrl, string urlPath, int id)
        {
            IPHostEntry hostEntry = Dns.GetHostEntry(baseUrl);

            while (hostEntry == null)
            {
                try
                {
                    hostEntry = Dns.GetHostEntry(baseUrl);
                }
                catch (SocketException)
                {
                    Console.WriteLine("Error: Unable to resolve host");
                    Thread.Sleep(1000);
                }
            }
            var ipAdress = hostEntry.AddressList[0];

            return new ExtendedSocket(baseUrl, urlPath, ipAdress, id);
        }

        public ExtendedSocket(string Host, string Path, IPAddress ipAdress, int id) : base(ipAdress.AddressFamily, SocketType.Stream, ProtocolType.Tcp)
        {
            this.Host = Host;
            this.Path = Path;
            this.Id = id;
            endPoint = new IPEndPoint(ipAdress, 80);
        }

        public void Start(Action<ExtendedSocket> onConnected)
        {
            BeginConnect(endPoint, ar =>
            {
                EndConnect(ar);
                onConnected(this);
            }, null);
        }

        public void StartSend(Action<ExtendedSocket> onSent)
        {
            string request = $"GET {Path} HTTP/1.1\r\nHost: {Host}\r\nConnection: close\r\n\r\n";
            byte[] requestBytes = Encoding.ASCII.GetBytes(request);
            BeginSend(requestBytes, 0, requestBytes.Length, SocketFlags.None, ar =>
            {
                var bytesSent = EndSend(ar);
                onSent(this);
            }, null);
        }

        public void StartReceive(Action<ExtendedSocket> onReceived)
        {
            BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, ar =>
            {
                EndReceive(ar);
                HandleReceivedResult(ar, buffer, onReceived);
            }, null);
        }

        private void HandleReceivedResult(IAsyncResult ar, byte[] buffer, Action<ExtendedSocket> onReceived)
        {
            int bytesRead = EndReceive(ar);
            if (bytesRead > 0)
            {
                if (headerBuilder.Length == 0)
                {
                    string headers = Encoding.ASCII.GetString(buffer, 0, bytesRead);
                    headerBuilder.Append(headers);

                    if (headerBuilder.ToString().Contains("\r\n\r\n"))
                    {
                        string headerString = headerBuilder.ToString();
                        int index = headerString.IndexOf("\r\n\r\n");
                        string headerPart = headerString.Substring(0, index + 4);
                        OnlyHeader = new StringBuilder(headerPart);

                        if (headerPart.Contains("Content-Length:"))
                        {
                            int start = headerPart.IndexOf("Content-Length:") + 16;
                            int end = headerPart.IndexOf("\r\n", start);
                            contentLength = int.Parse(headerPart.Substring(start, end - start));
                        }
                        else if (headerPart.Contains("content-length:"))
                        {
                            int start = headerPart.IndexOf("content-length:") + 16;
                            int end = headerPart.IndexOf("\r\n", start);
                            contentLength = int.Parse(headerPart.Substring(start, end - start));
                        }
                        //bytesReceived += bytesRead - (index + 4);

                        if (!headerBuilder.ToString().Contains("</html>"))
                        {
                            StartReceive(onReceived);
                        }
                        else
                        {
                            onReceived(this);
                        }
                    }
                    else
                    {
                        StartReceive(onReceived);
                    }
                }
                //else
                //{
                //    bytesReceived += bytesRead;
                //    if (bytesReceived < contentLength)
                //    {
                //        StartReceive(onReceived);
                //    }
                //    else
                //    {
                //        onReceived(this);
                //    }
                //}
            }
        }


        public Task BeginConnectAsync()
        {
            var taskCompletion = new TaskCompletionSource();
            Start(ar => taskCompletion.TrySetResult());
            return taskCompletion.Task;
        }

        public Task<int> BeginSendAsync()
        {
            var taskCompletion = new TaskCompletionSource<int>();
            StartSend(_ => taskCompletion.TrySetResult(0)); 
            return taskCompletion.Task;
        }

        public Task BeginReceiveAsync()
        {
            var taskCompletion = new TaskCompletionSource();
            StartReceive(_ => taskCompletion.TrySetResult());
            return taskCompletion.Task;
        }


        public void ShutdownAndClose()
        {
            Shutdown(SocketShutdown.Both);
            Close();
        }
    }
}
