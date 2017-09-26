public class primAndDijkstra {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int source;
		int size = 8;
		int [][] matrix = new int [size*size][size*size]; 
		int [] maxWeight = new int [size*size];     
		int [] maxWeightEdge = new int [size*size]; 
		int [] maxDist = new int [size*size];       
		int [] maxDistEdge = new int [size*size];   
		boolean [] inMST = new boolean[size*size];  
		boolean [] inSPT = new boolean[size*size];  
		boolean [][] edgeMST = new boolean [size*size][size*size];  
		boolean [][] edgeSPT = new boolean [size*size][size*size]; 
		int maxWeightAll, maxWeightNode, maxDistAll, maxDistNode;
		
		
		for (int i=1; i <= size; i++) {
			inMST[i] = false;
			inSPT[i] = false;
			for (int j=1; j <= size; j++) {
				matrix[i][j] = -1;
				edgeMST[i][j] = false; 
				edgeSPT[i][j] = false; 
			}
		}
		
		//constructing the graph
		matrix[1][2] = matrix[2][1] = 16;
		matrix[1][3] = matrix[3][1] = 8;
		matrix[1][5] = matrix[5][1] = 15;
		matrix[2][4] = matrix[4][2] = 2;
		matrix[3][4] = matrix[4][3] = 13;
		matrix[3][5] = matrix[5][3] = 17;
		matrix[3][6] = matrix[6][3] = 4;
		matrix[4][7] = matrix[7][4] = 3;
		matrix[5][6] = matrix[6][5] = 5;
		matrix[6][7] = matrix[7][6] = 18;
		matrix[6][8] = matrix[8][6] = 12;
		matrix[7][8] = matrix[8][7] = 9;

		source = 6;
		inMST[source] = true; 
		inSPT[source] = true;
		System.out.println("Source node: " + source + "\n");
		
		
		for (int i=1; i <= size; i++) {
			if ((i != source) && (matrix[source][i] != -1)) {
				maxWeight[i] = maxDist[i] = matrix[source][i];
				maxWeightEdge[i] = maxDistEdge[i] = source;
			}
			else maxWeight[i] = maxDist[i]= 0;
		}
		
		maxWeightNode = maxDistNode = source;
		
		for (int i=1; i < size; i++) { 
			maxWeightAll = maxDistAll = 0;
			for (int j=1; j <= size; j++) { 
				if ((!inMST[j]) && (maxWeight[j] > maxWeightAll)) {
					maxWeightAll = maxWeight[j];
					maxWeightNode = j;
				}
				if ((!inSPT[j]) && (maxDist[j] > maxDistAll)) {
					maxDistAll = maxDist[j];
					maxDistNode = j;
				}
			}

			inMST[maxWeightNode] = true;
			edgeMST[maxWeightNode][maxWeightEdge[maxWeightNode]] = edgeMST[maxWeightEdge[maxWeightNode]][maxWeightNode] = true; 
			
			inSPT[maxDistNode] = true;
			edgeSPT[maxDistNode][maxDistEdge[maxDistNode]] = edgeSPT[maxDistEdge[maxDistNode]][maxDistNode] = true; 
			for (int j=1; j <= size; j++) {
				if ((!inMST[j]) && (matrix[j][maxWeightNode] != -1))
					if (matrix[j][maxWeightNode] > maxWeight[j]) {
						maxWeight[j] = matrix[j][maxWeightNode];
						maxWeightEdge[j] = maxWeightNode;
					}
				if ((!inSPT[j]) && (matrix[j][maxDistNode] != -1))
					if (maxDist[maxDistNode] + matrix[maxDistNode][j] > maxDist[j]) {
						maxDist[j] = maxDist[maxDistNode] + matrix[maxDistNode][j];
						maxDistEdge[j] = maxDistNode;
					}
			}

		}
		
		int sumWeight = 0;
		System.out.println("MST edges on Prim's Algorithm:");
		for (int i=1; i <= size; i++)
			for (int j=i+1; j <= size; j++)
				if (edgeMST[i][j]) {
					System.out.println(i + " - " + j);
					sumWeight += matrix[i][j];
				}
		System.out.println("\nTotal weight = " + sumWeight + "\n");

		sumWeight = 0;
		System.out.println("SPT edges on Dijkstra's Algorithm:");
		for (int i=1; i <= size; i++)
			for (int j=i+1; j <= size; j++)
				if (edgeSPT[i][j]) {
					System.out.println(i + " - " + j);
					sumWeight += matrix[i][j];
				}
		System.out.println("\nTotal weight = " + sumWeight + "\n");
}
}