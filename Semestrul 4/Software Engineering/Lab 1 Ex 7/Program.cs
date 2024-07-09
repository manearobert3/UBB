using System;
using System.Numerics;

internal class Program
{
    static void Main(String[] args)
    {
        Console.WriteLine("Enter n for matrix dimension:");
        int matrixDimension =Convert.ToInt32(Console.ReadLine());
        Console.WriteLine("Your n is : " + matrixDimension);
        int[,] array = new int[matrixDimension, matrixDimension];
        for (int i = 0; i < matrixDimension; i++)
            for (int j = 0; j < matrixDimension; j++)
            {
                
                array[i, j] = Convert.ToInt32(Console.ReadLine());
            }
        for (int i = 0; i < matrixDimension; i++)
        {
            for (int j = 0; j < matrixDimension; j++)
            
                Console.Write(array[i, j] + " ");
                Console.Write("\n");

            
        }
        for (int i = 0; i < matrixDimension / 2; i++)
        {
            for (int j = i; j < matrixDimension - i - 1; j++)
            {
                int aux = array[i, j];
                array[i, j] = array[matrixDimension - 1 - j, i];
                array[matrixDimension - 1 - j, i] = array[matrixDimension - 1 - i, matrixDimension - 1 - j];
                array[matrixDimension - 1 - i, matrixDimension - 1 - j] = array[j, matrixDimension - 1 - i];
                array[j, matrixDimension - 1 - i] = aux;
            }
            
        }

            for (int i = 0; i < matrixDimension; i++)
        {
            for (int j = 0; j < matrixDimension; j++)
            
                Console.Write(array[i, j]+" ");
                Console.Write("\n");

            }
        
    }
}