public class Determinant {

    private static int recursiveDeterminant(int[][] matrix){
        int size = matrix.length;
        int det = 0;

        if (size == 2){
            det = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
            return det;
        }
        else {
            for (int i = 0; i < size; i++){
                int coefficient = matrix[0][i];
                det += coefficient * (findCofactor(0, i, matrix));
            }
            return det;
        }
    }

    private static int[][] removeColumnAndRow(int rowIndex, int columnIndex, int[][] matrix){
        int newSize = matrix.length - 1;
        int[][] newMatrix = new int[newSize][newSize];
        int newRowCount = 0, newColumnCount = 0;

        for (int i = 0; i <= newSize; i++){
            if (i != rowIndex){
                newColumnCount = 0;
                for (int j = 0; j <= newSize; j++){
                    if (j != columnIndex){
                        newMatrix[newRowCount][newColumnCount] = matrix[i][j];
                        newColumnCount++;
                    }

                }
                newRowCount++;
            }
        }
        return newMatrix;
    }

    private static int findCofactor(int row, int column, int[][] matrix){
        int[][] minor = removeColumnAndRow(row, column, matrix);
        int power = (int) Math.pow(-1, row+column);
        int det = recursiveDeterminant(minor) * power;
        return det;
    }

}
