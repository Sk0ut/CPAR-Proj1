using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CPAR
{
    class Program
    {
        static void OnMult(int m_ar, int m_br)
        {
            double temp;
            int i, j, k;

            double[] pha = new double[m_ar * m_ar], phb = new double[m_ar * m_ar], phc = new double[m_ar * m_ar];
            
            for (i = 0; i < m_ar; i++)
                for (j = 0; j < m_ar; j++)
                    pha[i * m_ar + j] = (double)1.0;

            for (i = 0; i < m_br; i++)
                for (j = 0; j < m_br; j++)
                    phb[i * m_br + j] = (double)(i + 1);

            var watch = System.Diagnostics.Stopwatch.StartNew();

            for (i = 0; i < m_ar; i++)
            {
                for (j = 0; j < m_br; j++)
                {
                    temp = 0;
                    for (k = 0; k < m_ar; k++)
                    {
                        temp += pha[i * m_ar + k] * phb[k * m_br + j];
                    }
                    phc[i * m_ar + j] = temp;
                }
            }

            watch.Stop();

            Console.WriteLine("Time: " + watch.ElapsedMilliseconds/1000.0 + " seconds\n");
            Console.WriteLine("Result matrix: ");

            for (i = 0; i < 1; i++) {
                for (j = 0; j < Math.Min(10, m_br); j++)
                    Console.WriteLine(phc[j] + " ");
            }
            Console.WriteLine();
        }


        static void OnMultLine(int m_ar, int m_br)
        {
            int i, j, k;

            double[] pha = new double[m_ar * m_ar], phb = new double[m_ar * m_ar], phc = new double[m_ar * m_ar];

            for (i = 0; i < m_ar; i++)
                for (j = 0; j < m_ar; j++)
                    pha[i * m_ar + j] = (double)1.0;

            for (i = 0; i < m_br; i++)
                for (j = 0; j < m_br; j++)
                    phb[i * m_br + j] = (double)(i + 1);

            var watch = System.Diagnostics.Stopwatch.StartNew();

            for (i = 0; i < m_ar; i++)
            {
                for (j = 0; j < m_ar; j++)
                {
                    for (k = 0; k < m_br; k++)
                    {
                        phc[i * m_ar + k] += pha[i * m_ar + k] * phb[j * m_br + k];
                    }
                }
            }

            watch.Stop();

            Console.WriteLine("Time: " + watch.ElapsedMilliseconds / 1000.0 + " seconds\n");
            Console.WriteLine("Result matrix: ");

            for (i = 0; i < 1; i++)
            {
                for (j = 0; j < Math.Min(10, m_br); j++)
                    Console.WriteLine(phc[j] + " ");
            }
            Console.WriteLine();
        }


        float produtoInterno(float[] v1, float[] v2, int col)
        {
            int i;
            float soma = (float)0.0;

            for (i = 0; i < col; i++)
                soma += v1[i] * v2[i];

            return (soma);
        }

        static void Main(string[] args)
        {
            int lin, col;
            int op = 1;

            do
            {
                Console.WriteLine("\n1. Multiplication");
                Console.WriteLine("2. Line Multiplication");
                Console.Write("Selection?: ");
                op = Convert.ToInt32(Console.ReadLine());
                if (op == 0)
                    break;
                Console.Write("Dimensions: lins cols ? ");
                lin = Convert.ToInt32(Console.ReadLine());
                col = Convert.ToInt32(Console.ReadLine());  

                switch (op)
                {
                    case 1:
                        OnMult(lin, col);
                        break;
                    case 2:
                        OnMultLine(lin, col);

                        break;
                }

            } while (op != 0);
        }
    }
}
