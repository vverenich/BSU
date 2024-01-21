package task23;

import java.io.*;
import java.util.Scanner;

public class Code23{

    public static void parseToWord(int number) throws Exception {
    	if (number < 1 || number > 1000000000) {
    		System.out.println("number must be less, than 1000000000 and more, than 0");
    		return;
    	}
    	if (number == 10) {
    		System.out.println(number + " - ������");
    		return;
    	}
    	int[] array_int = new int[4];
        String[][] array_string = new String[][] {
        	{" ��������", " ���������", " ����������"},
            {" �������", " ��������", " ���������"},
            {" ������", " ������", " �����"},
            {"", "", ""}
            };
        array_int[0] = (number - (number % 1000000000)) / 1000000000;
        array_int[1] = ((number % 1000000000) - (number % 1000000)) / 1000000;
        array_int[2] = ((number % 1000000) - (number % 1000)) / 1000;
        array_int[3] = number % 1000;
        String result = "";
        for (int i = 0; i < 4; i++)
        {
            if (array_int[i] != 0)
            {
                if (((array_int[i] - (array_int[i] % 100)) / 100) != 0)
                    switch (((array_int[i] - (array_int[i] % 100)) / 100))
                    {
                        case 1: result += " ���"; break;
                        case 2: result += " ������"; break;
                        case 3: result += " ������"; break;
                        case 4: result += " ���������"; break;
                        case 5: result += " �������"; break;
                        case 6: result += " ��������"; break;
                        case 7: result += " �������"; break;
                        case 8: result += " ���������"; break;
                        case 9: result += " ���������"; break;
                    }
                if (((array_int[i] % 100) - ((array_int[i] % 100) % 10)) / 10 != 1)
                {
                    switch (((array_int[i] % 100) - ((array_int[i] % 100) % 10)) / 10)
                    {
                        case 2: result += " ��������"; break;
                        case 3: result += " ��������"; break;
                        case 4: result += " �����"; break;
                        case 5: result += " ���������"; break;
                        case 6: result += " ����������"; break;
                        case 7: result += " ���������"; break;
                        case 8: result += " �����������"; break;
                        case 9: result += " ���������"; break;
                    }
                }
                switch (array_int[i] % 10)
                {
                    case 1: if (i == 2) result += " ����"; else result += " ����"; break;
                    case 2: if (i == 2) result += " ���"; else result += " ���"; break;
                    case 3: result += " ���"; break;
                    case 4: result += " ������"; break;
                    case 5: result += " ����"; break;
                    case 6: result += " �����"; break;
                    case 7: result += " ����"; break;
                    case 8: result += " ������"; break;
                    case 9: result += " ������"; break;
                }
            }
            else switch (array_int[i] % 100)
                {
                    case 10: result += " ������"; break;
                    case 11: result += " �����������"; break;
                    case 12: result += " ����������"; break;
                    case 13: result += " ����������"; break;
                    case 14: result += " ������������"; break;
                    case 15: result += " ����������"; break;
                    case 16: result += " �����������"; break;
                    case 17: result += " ����������"; break;
                    case 18: result += " �������������"; break;
                    case 19: result += " ������������"; break;
                }
            if (array_int[i] % 100 >= 10 && array_int[i] % 100 <= 19) result += " " + array_string[i][2] + " ";
            else switch (array_int[i] % 10)
                {
                    case 1: result += " " + array_string[i][0] + " "; break;
                    case 2:
                    case 3:
                    case 4: result += " " + array_string[i][1] + " "; break;
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9: result += " " + array_string[i][2] + " "; break;
                }
        }
        System.out.println(number + " - " + result);
    }
    public static void task23(String path) throws Exception {
    	try(Scanner scanner = new Scanner(new File(path)))
    	{
    	    //������ ���������
    	    String line;
    	    while(scanner.hasNextLine()){
    	    	line = scanner.nextLine();
                parseToWord(Integer.parseInt(line));
    	    }
    	} catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception ex) {
        	System.out.println(ex.getMessage());
        }
    }
}
