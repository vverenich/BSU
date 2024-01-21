using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Runtime;
using SharedCGAL;
using System;
using Autodesk.AutoCAD.Colors;
using Autodesk.AutoCAD.Geometry;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SharedCGAL
{
    internal class Simplex
    {
        //basis, value, hasAlternative
        public static ValueTuple<double[], double, bool> Maximize(double[] c, double[][] A, double[] b)
        {
            int n = c.Length, m = b.Length;

            if (n <= m)
                throw new System.Exception("n <= m");

            int[] rowIndexBasisValue, columnIndexFreeValue;

            var tableau = ToTableau(c, A, b, out rowIndexBasisValue, out columnIndexFreeValue);

            if (!IsJoint(tableau))
                throw new System.Exception("Constraints system is not joint");

            while (true)
            {

                var basisSolution = FormSolution(tableau, rowIndexBasisValue);

                if (!IsJoint(tableau))
                    throw new System.Exception("Constraints system is not joint");

                if (IsAcceptable(basisSolution) && isOptimal(tableau))
                {
                    return (basisSolution, tableau[tableau.Length - 1][0], HasAlternative(tableau));
                }
                else
                {
                    var pivotPosition = GetPivotElementPosition(tableau);

                    if (pivotPosition.Item2 == -1)
                        throw new System.Exception("Objective function is not limited");

                    Pivot(in pivotPosition, ref tableau, ref rowIndexBasisValue, ref columnIndexFreeValue);
                }
            }
        }


        private static double[][] ToTableau(double[] c, double[][] A, double[] b, out int[] rowIndexBasisValue, out int[] columnIndexFreeValue)
        {
            rowIndexBasisValue = new int[A.Length];
            for (int i = 0; i < rowIndexBasisValue.Length; i++)
                rowIndexBasisValue[i] = -1;

            columnIndexFreeValue = new int[A[0].Length - A.Length + 1];
            columnIndexFreeValue[0] = -1;

            int currentColumnIndex = 0;
            for (int i = 0; i < A[0].Length; i++)
            {
                int zeroAmount = 0, oneAmount = 0, oneRowIndex = -1;
                for (int j = 0; j < A.Length; j++)
                {
                    if (A[j][i] == 1)
                    {
                        oneAmount++;
                        oneRowIndex = j;
                    }
                    else if (A[j][i] == 0)
                    {
                        zeroAmount++;
                    }
                }

                if (zeroAmount == A.Length - 1 && oneAmount == 1)
                {

                    if (rowIndexBasisValue[oneRowIndex] == -1)
                    {
                        rowIndexBasisValue[oneRowIndex] = i;
                    }
                    else throw new System.Exception("several ones on one row");
                }
                else
                {
                    if (++currentColumnIndex >= columnIndexFreeValue.Length)
                    {
                        throw new System.Exception("Too much free variables");
                    }
                    columnIndexFreeValue[currentColumnIndex] = i;
                }

            }

            for (int i = 0; i < rowIndexBasisValue.Length; i++)
            {
                if (rowIndexBasisValue[i] == -1)
                    throw new System.Exception("Not enough basis variables");
            }

            double[][] tableau = new double[b.Length + 1][];
            for (int i = 0; i < tableau.Length; i++)
            {
                tableau[i] = new double[A[0].Length - b.Length + 1];
            }

            for (int i = 0; i < tableau.Length - 1; i++)
            {
                tableau[i][0] = b[i];
            }

            for (int i = 1; i < tableau[tableau.Length - 1].Length; i++)
            {
                tableau[tableau.Length - 1][i] = -c[columnIndexFreeValue[i]];
            }

            for (int i = 0; i < tableau.Length - 1; i++)
            {
                for (int j = 1; j < tableau[0].Length; j++)
                {
                    tableau[i][j] = A[i][columnIndexFreeValue[j]];
                }
            }

            return tableau;
        }

        private static bool IsJoint(double[][] tableau)
        {
            for (int i = 0; i < tableau.Length - 1; i++)
            {
                if (tableau[i][0] < 0)
                {
                    bool hasNegative = false;
                    for (int j = 1; j < tableau[i].Length; j++)
                    {
                        if (tableau[i][j] < 0)
                        {
                            hasNegative = true;
                            break;
                        }
                    }

                    if (!hasNegative)
                    {
                        return false;
                    }

                }
            }

            return true;
        }

        private static double[] FormSolution(double[][] tableau, int[] rowIndexBasisValue)
        {
            double[] solution = new double[tableau.Length + tableau[0].Length - 2];
            for (int i = 0; i < tableau.Length - 1; i++)
            {
                solution[rowIndexBasisValue[i]] = tableau[i][0];
            }

            return solution;
        }

        private static bool IsAcceptable(double[] solution)
        {
            foreach (var element in solution)
            {
                if (element < 0)
                    return false;
            }

            return true;
        }

        private static bool isOptimal(double[][] tableau)
        {
            for (int i = 1; i < tableau[tableau.Length - 1].Length; i++)
            {
                if (tableau[tableau.Length - 1][i] < 0)
                {
                    return false;
                }
            }

            return true;
        }

        private static bool HasAlternative(double[][] tableau)
        {
            for (int i = 1; i < tableau[tableau.Length - 1].Length; i++)
            {
                if (Math.Abs(tableau[tableau.Length - 1][i]) <= double.Epsilon)
                {
                    return true;
                }
            }
            return false;
        }

        private static ValueTuple<int, int> GetPivotElementPosition(double[][] tableau)
        {
            int minColumnIndex = -1;
            double minValue = double.MaxValue;

            for (int i = 1; i < tableau[tableau.Length - 1].Length; i++)
            {
                if (tableau[tableau.Length - 1][i] < minValue)
                {
                    minColumnIndex = i;
                    minValue = tableau[tableau.Length - 1][i];
                }
            }

            int minRowIndex = -1;
            double minPosValue = Double.MaxValue;
            for (int i = 0; i < tableau.Length - 1; i++)
            {
                double temp = tableau[i][0] / tableau[i][minColumnIndex];
                if (temp < minPosValue && temp > 0)
                {
                    minRowIndex = i;
                    minPosValue = temp;
                }
            }

            return (minRowIndex, minColumnIndex);
        }

        private static void Pivot(in ValueTuple<int, int> pivotPosition, ref double[][] tableau, ref int[] rowIndexBasisValue, ref int[] columnIndexFreeValue)
        {
            if (pivotPosition.Item1 == -1)
                throw new System.Exception("Objective function is not limited");

            // basis <-> free
            var temp = rowIndexBasisValue[pivotPosition.Item1];
            rowIndexBasisValue[pivotPosition.Item1] = columnIndexFreeValue[pivotPosition.Item2];
            columnIndexFreeValue[pivotPosition.Item2] = temp;

            // pivot element
            var pivotElement = tableau[pivotPosition.Item1][pivotPosition.Item2];
            tableau[pivotPosition.Item1][pivotPosition.Item2] = 1 / tableau[pivotPosition.Item1][pivotPosition.Item2];

            // other elements
            for (int i = 0; i < tableau.Length; i++)
            {
                if (i == pivotPosition.Item1)
                    continue;

                for (int j = 0; j < tableau[0].Length; j++)
                {
                    if (j == pivotPosition.Item2)
                        continue;

                    tableau[i][j] -= tableau[i][pivotPosition.Item2] * tableau[pivotPosition.Item1][j] / pivotElement;
                }
            }

            //pivot row
            for (int i = 0; i < tableau[pivotPosition.Item1].Length; i++)
            {
                if (i != pivotPosition.Item2)
                {
                    tableau[pivotPosition.Item1][i] /= pivotElement;
                }
            }

            //pivot column
            for (int i = 0; i < tableau.Length; i++)
            {
                if (i != pivotPosition.Item1)
                {
                    tableau[i][pivotPosition.Item2] /= -pivotElement;
                }
            }

        }

    }
    public class Plugin
    {

        private enum ConstraintSign { LE, ME };

        [CommandMethod("Simplex")]
        public void Start()
        {
            Database dbCurrent = Application.DocumentManager.MdiActiveDocument.Database;
            Document doc = Application.DocumentManager.MdiActiveDocument;
            Editor ed = doc.Editor;
            int constraintsAmount;
            double[][] startA;
            double[] startb;
            double[] startc;
            ConstraintSign[] startSigns;


            var promptAmount = ed.GetInteger("Enter lines amount:");

            if (promptAmount.Status != PromptStatus.OK)
            {
                ed.WriteMessage($"Error: status - {promptAmount.Status}");
                return;
            }

            constraintsAmount = promptAmount.Value;
            if (constraintsAmount <= 0)
            {
                ed.WriteMessage($"Error: lines amount should be positive ({constraintsAmount})");
                return;
            }
            startA = new double[constraintsAmount][];
            startb = new double[constraintsAmount];
            startc = new double[2];

            startSigns = new ConstraintSign[constraintsAmount];

            using (Transaction tr = doc.TransactionManager.StartTransaction())
            {
                for (int i = 0; i < constraintsAmount;)
                {
                    PromptEntityResult promptLine = ed.GetEntity($"Select {i + 1} XLine: ");
                    if (promptLine.Status != PromptStatus.OK)
                    {
                        ed.WriteMessage($"Error: status - {promptLine.Status}");
                        continue;
                    }

                    Xline tempXline = tr.GetObject(promptLine.ObjectId, OpenMode.ForWrite) as Xline;
                    if (tempXline == null)
                    {
                        ed.WriteMessage($"Error: that's not Xline");
                        continue;
                    }

                    double[] lineRow = new double[2];
                    double tempb;
                    FormLineRow(tempXline, ref lineRow, out tempb);
                    startA[i] = lineRow;
                    startb[i] = tempb;

                    var prompt_point = ed.GetPoint("Choose the half-plane:");
                    if (prompt_point.Status != PromptStatus.OK)
                    {
                        ed.WriteMessage($"Error: status - {prompt_point.Status}");
                        continue;
                    }

                    startSigns[i] = GetSign(prompt_point.Value, lineRow, tempb);

                    i++;
                }

                var promptXcoeff = ed.GetDouble("Choose x coeff:");
                if (promptXcoeff.Status != PromptStatus.OK)
                {
                    ed.WriteMessage($"Error: status - {promptXcoeff.Status}");
                    return;
                }

                var promptYcoeff = ed.GetDouble("Choose y coeff:");
                if (promptYcoeff.Status != PromptStatus.OK)
                {
                    ed.WriteMessage($"Error: status - {promptXcoeff.Status}");
                    return;
                }

                startc[0] = promptXcoeff.Value;
                startc[1] = promptYcoeff.Value;

                double[][] preparedA = GetCanonicalForm(startA, ref startb, startSigns, ref startc);

                try
                {
                    var result = Simplex.Maximize(startc, preparedA, startb);

                    ed.WriteMessage("SOLUITION:");
                    for (int i = 0; i < result.Item1.Length; i++)
                    {
                        ed.WriteMessage($"x{i + 1}: {result.Item1[i]}");
                    }

                    BlockTable bt = (BlockTable)tr.GetObject(dbCurrent.BlockTableId, OpenMode.ForRead, false);
                    BlockTableRecord btr =
                        (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite, false);

                    DBPoint point = new DBPoint(new Point3d(result.Item1[0], result.Item1[1], 0));
                    point.Thickness = 200;
                    point.ColorIndex = 4;
                    btr.AppendEntity(point);
                    tr.AddNewlyCreatedDBObject(point, true);
                    ed.WriteMessage($"Point: ({result.Item1[0]:F4}; {result.Item1[1]:F4})");
                    ed.WriteMessage($"Value: {result.Item2}");
                    ed.WriteMessage($"Has alternative value: {result.Item3}");
                }
                catch (System.Exception ex)
                {
                    ed.WriteMessage($"Error: {ex.Message}");
                }


                tr.Commit();
            }
        }

        private static void FormLineRow(Xline xline, ref double[] row, out double b_value)
        {
            Point3d pointA = xline.BasePoint,
                pointB = xline.BasePoint + (1000 * xline.UnitDir);

            row[0] = pointA.Y - pointB.Y;
            row[1] = pointB.X - pointA.X;

            b_value = pointA.Y * (pointB.X - pointA.X) - pointA.X * (pointB.Y - pointA.Y);
        }

        private static ConstraintSign GetSign(Point3d point, double[] row, double b_value)
        {
            if (row[0] * point.X + row[1] * point.Y <= b_value)
                return ConstraintSign.LE;
            else
                return ConstraintSign.ME;
        }

        private static double[][] GetCanonicalForm(double[][] A, ref double[] b, ConstraintSign[] signs, ref double[] c)
        {
            var result = new double[A.Length][];
            for (int i = 0; i < result.Length; ++i)
            {
                result[i] = new double[A[0].Length + A.Length];
            }

            Array.Resize(ref c, c.Length + A.Length);

            int ratio;
            for (int i = 0; i < A.Length; ++i)
            {
                if (signs[i] == ConstraintSign.ME)
                {
                    ratio = -1;
                    b[i] *= ratio;
                    //  signs[i] = ConstraintSign.LE;
                }
                else
                {
                    ratio = 1;
                }

                for (int j = 0; j < A[0].Length; ++j)
                {
                    result[i][j] = A[i][j] * ratio;
                    result[i][A[0].Length + i] = 1;
                }
            }

            return result;
        }
    }
}