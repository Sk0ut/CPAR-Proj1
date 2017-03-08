import java.util.Scanner;

public class MatrixProd {
	 
	static void OnMult(int m_ar, int m_br) 
	{		
		long Time1, Time2;
		
		double temp;
		int i, j, k;

		double pha[] = new double[m_ar * m_ar], phb[] = new double[m_ar * m_ar], phc[] = new double[m_ar * m_ar];
		

		for(i=0; i<m_ar; i++)
			for(j=0; j<m_ar; j++)
				pha[i*m_ar + j] = (double)1.0;

		for(i=0; i<m_br; i++)
			for(j=0; j<m_br; j++)
				phb[i*m_br + j] = (double)(i+1);

	    Time1 = System.currentTimeMillis();

		for(i=0; i<m_ar; i++)
		{	for( j=0; j<m_br; j++)
			{	temp = 0;
				for( k=0; k<m_ar; k++)
				{	
					temp += pha[i*m_ar+k] * phb[k*m_br+j];
				}
				phc[i*m_ar+j]=temp;
			}
		}


	    Time2 = System.currentTimeMillis();
	    System.out.println("Time: " + (Time2 - Time1)/1000.0 + " seconds\n");
	    System.out.println("Result matrix: ");
	    
		for(i=0; i<1; i++) {	
			for(j=0; j < Math.min(10, m_br); j++)
				System.out.println(phc[j] + " ");
		}
		System.out.println();
	}


	static void OnMultLine(int m_ar, int m_br)
	{
		long Time1, Time2;
		
		double temp;
		int i, j, k;

		double pha[] = new double[m_ar * m_ar], phb[] = new double[m_ar * m_ar], phc[] = new double[m_ar * m_ar];
		

		for(i=0; i<m_ar; i++)
			for(j=0; j<m_ar; j++)
				pha[i*m_ar + j] = (double)1.0;

		for(i=0; i<m_br; i++)
			for(j=0; j<m_br; j++)
				phb[i*m_br + j] = (double)(i+1);

	    Time1 = System.currentTimeMillis();

	    for(i=0; i<m_ar; i++)
		{	
			for( j=0; j<m_ar; j++) 
			{
				for( k=0; k<m_br; k++)
				{	
					phc[i*m_ar+k] += pha[i*m_ar+k] * phb[j*m_br+k];
				}
			}
		}


	    Time2 = System.currentTimeMillis();
	    System.out.println("Time: " + (Time2 - Time1)/1000.0 + " seconds\n");
	    System.out.println("Result matrix: ");
	    
		for(i=0; i<1; i++) {	
			for(j=0; j < Math.min(10, m_br); j++)
				System.out.println(phc[j] + " ");
		}
		System.out.println();	    
	}


	float produtoInterno(float v1[], float v2[], int col)
	{
		int i;
		float soma = (float) 0.0;	

		for(i=0; i<col; i++)
			soma += v1[i]*v2[i];
		
		return(soma);
	}

	public static void main(String [] args)
	{
		int lin, col;
		int op = 1;
		
	  	Scanner s = new Scanner(System.in);
		
		do {
			System.out.println("\n1. Multiplication");
			System.out.println("2. Line Multiplication");
			System.out.print("Selection?: ");
			op = s.nextInt();
			if (op == 0)
				break;
			System.out.print("Dimensions: lins cols ? ");
			lin = s.nextInt();
			col = s.nextInt();

			switch (op){
				case 1: 
					OnMult(lin, col);
					break;
				case 2:
					OnMultLine(lin, col);
	    
					break;
			}
			
		}while (op != 0);
		
		s.close();
	}
}
