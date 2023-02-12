using System.Windows.Forms;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.Geometry;
using System.Collections.Generic;
using System;

using Autodesk.AutoCAD.ApplicationServices;

using Autodesk.AutoCAD.DatabaseServices;

using Autodesk.AutoCAD.Runtime;

using Autodesk.AutoCAD.EditorInput;

using Autodesk.AutoCAD.Geometry;

using System;
using Application = Autodesk.AutoCAD.ApplicationServices.Application;


public class Lexicograg
{

    static Boolean onSegment(Point3d p, Point3d q, Point3d r)
    {
        if (q.X <= Math.Max(p.X, r.X) && q.X >= Math.Min(p.X, r.X) &&
            q.Y <= Math.Max(p.Y, r.Y) && q.Y >= Math.Min(p.Y, r.Y))
            return true;

        return false;
    }

    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    static int orientation(Point3d p, Point3d q, Point3d r)
    {
        // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
        // for details of below formula.
        double val = (q.Y - p.Y) * (r.X - q.X) -
                (q.X - p.X) * (r.Y - q.Y);

        if (val == 0) return 0; // collinear

        return (val > 0) ? 1 : 2; // clock or counterclock wise
    }

    // The main function that returns true if line segment 'p1q1'
    // and 'p2q2' intersect.
    static Boolean doIntersect(Point3d p1, Point3d q1, Point3d p2, Point3d q2)
    {
        if (p1 == p2 || p1 == q2 || q1 == p2 || q1 == q2)
        {
            return false;
        }


        // Find the four orientations needed for general and
        // special cases
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        // General case
        if (o1 != o2 && o3 != o4)
            return true;

        return false;

        // Special Cases
        // p1, q1 and p2 are collinear and p2 lies on segment p1q1
        if (o1 == 0 && onSegment(p1, p2, q1)) return true;

        // p1, q1 and q2 are collinear and q2 lies on segment p1q1
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;

        // p2, q2 and p1 are collinear and p1 lies on segment p2q2
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;

        // p2, q2 and q1 are collinear and q1 lies on segment p2q2
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false; // Doesn't fall in any of the above cases
    }


    public double Cross(double x1, double y1, double x2, double y2)
    {
        return (x1 * y2) - (x2 * y1);
    }



    [CommandMethod("LEXTRIANG")]

    public void TriangulateCommand()

    {

        const int maxpoints = 32767;



        Document doc =

          Application.DocumentManager.MdiActiveDocument;

        Database db = doc.Database;

        Editor ed = doc.Editor;



        TypedValue[] tvs = { new TypedValue(0, "POINT") };

        SelectionFilter sf =

          new SelectionFilter(tvs);

        PromptSelectionOptions pso = new PromptSelectionOptions();

        pso.MessageForAdding = "Select Points:";

        pso.AllowDuplicates = false;

        PromptSelectionResult psr = ed.GetSelection(pso, sf);



        if (psr.Status == PromptStatus.Error) return;

        if (psr.Status == PromptStatus.Cancel) return;



        SelectionSet ss = psr.Value;

        int npts = ss.Count;

        if (npts < 3)

        {

            ed.WriteMessage("Minimum 3 points must be selected!");

            return;

        }

        if (npts > maxpoints)

        {

            ed.WriteMessage("Maximum nuber of points exceeded!");

            return;

        }



        int i, j, k, ntri, ned, status1 = 0, status2 = 0;

        bool status;



        // Point coordinates

        List<Point3d> points = new List<Point3d>();

        double[] ptx = new double[maxpoints + 3];

        double[] pty = new double[maxpoints + 3];

        double[] ptz = new double[maxpoints + 3];



        // Triangle definitions



        int[] pt1 = new int[maxpoints * 2 + 1];

        int[] pt2 = new int[maxpoints * 2 + 1];

        int[] pt3 = new int[maxpoints * 2 + 1];



        ObjectId[] idarray = ss.GetObjectIds();

        Transaction tr =

          db.TransactionManager.StartTransaction();

        using (tr)

        {

            DBPoint ent;

            k = 0;

            for (i = 0; i < npts; i++)

            {

                ent =

                  (DBPoint)tr.GetObject(idarray[k], OpenMode.ForRead, false);

                ptx[i] = ent.Position[0];

                pty[i] = ent.Position[1];

                ptz[i] = ent.Position[2];
                points.Add(new Point3d(ptx[i], pty[i], ptz[i]));

                // points[i].Add(new Vector3d(ptx[i], pty[i], ptz[i]));





                for (j = 0; j < i; j++)

                    if ((ptx[i] == ptx[j]) && (pty[i] == pty[j]))

                    {

                        i--; npts--; status2++;

                    }

                k++;

            }

            tr.Commit();

        }



        if (status2 > 0)

            ed.WriteMessage(

              "\nIgnored {0} point(s) with same coordinates.",

              status2

            );


        points.Sort((x, y) => x.X.CompareTo(y.X));


        tr = db.TransactionManager.StartTransaction();
        using (tr)
        {

            BlockTable acBlkTbl;
            acBlkTbl = tr.GetObject(db.BlockTableId,
                                         OpenMode.ForRead) as BlockTable;
            BlockTableRecord acBlkTblRec;
            acBlkTblRec = tr.GetObject(acBlkTbl[BlockTableRecord.ModelSpace],
                                            OpenMode.ForWrite) as BlockTableRecord;


            //MessageBox.Show(points[0].ToString());


            Line l1 = new Line(points[0], points[1]);
            Line l2 = new Line(points[1], points[2]);
            Line l3 = new Line(points[2], points[0]);




            List<Line> mvo = new List<Line>();
            List<Line> edges = new List<Line>();

            mvo.Add(l1);
            mvo.Add(l2);
            mvo.Add(l3);

            edges.Add(l1);
            edges.Add(l2);
            edges.Add(l3);


            int last = 2;
            for (int z = 3; z < npts; z++)
            {
                Point3d p = points[z];
                Point3d l = points[last];


                HashSet<Line> linesadd = new HashSet<Line>();
                List<Line> visible = new List<Line>();
                //List<Line> 
                foreach (Line e in mvo)
                {
                    Boolean isGood = true;
                    foreach (Line ll in edges)
                    {
                        if (ll == e)
                        {
                            continue;
                        }

                        if (doIntersect(p, e.StartPoint, ll.StartPoint, ll.EndPoint)
                            || doIntersect(p, e.EndPoint, ll.StartPoint, ll.EndPoint))
                        {
                            isGood = false;
                        }

                    }

                    if (isGood)
                    {
                        linesadd.Add(new Line(p, e.StartPoint));
                        linesadd.Add(new Line(p, e.EndPoint));
                        visible.Add(e);
                    }
                }



                double maxy = double.MinValue, miny = double.MaxValue;
                double maxx = double.MinValue, minx = double.MaxValue;
                double maxz = double.MinValue, minz = double.MaxValue;

                foreach (Line ll in visible)
                {
                    mvo.Remove(ll);
                }

                foreach (Line ll in linesadd)
                {
                    edges.Add(ll);

                    if (ll.EndPoint.Y > maxy)
                    {
                        maxy = ll.EndPoint.Y;
                        maxx = ll.EndPoint.X;
                        maxz = ll.EndPoint.Z;
                    }

                    if (ll.EndPoint.Y < miny)
                    {
                        miny = ll.EndPoint.Y;
                        minx = ll.EndPoint.X;
                        minz = ll.EndPoint.Z;
                    }

                    if (ll.StartPoint.Y > maxy)
                    {
                        maxy = ll.StartPoint.Y;
                        maxx = ll.StartPoint.X;
                        maxz = ll.StartPoint.Z;
                    }

                    if (ll.StartPoint.Y < miny)
                    {
                        miny = ll.StartPoint.Y;
                        minx = ll.StartPoint.X;
                        minz = ll.StartPoint.Z;
                    }

                }



                mvo.Add(new Line(p, new Point3d(maxx, maxy, maxz)));
                mvo.Add(new Line(p, new Point3d(minx, miny, minz)));




                last = z;
            }

            /*
            l1.SetDatabaseDefaults();
            acBlkTblRec.AppendEntity(l1);

            tr.AddNewlyCreatedDBObject(l1, true);

            l2.SetDatabaseDefaults();
            acBlkTblRec.AppendEntity(l2);

            tr.AddNewlyCreatedDBObject(l2, true);

            l3.SetDatabaseDefaults();
            acBlkTblRec.AppendEntity(l3);*/


            foreach (Line ll in edges)
            {
                ll.SetDatabaseDefaults();
                acBlkTblRec.AppendEntity(ll);
                tr.AddNewlyCreatedDBObject(ll, true);
            }

            //  tr.AddNewlyCreatedDBObject(l3, true);




            tr.Commit();
        }









        // Supertriangle



        //tr = db.TransactionManager.StartTransaction();

        //using (tr)

        //{

        //    BlockTable bt =

        //      (BlockTable)tr.GetObject(

        //        db.BlockTableId,

        //        OpenMode.ForRead,

        //        false

        //      );

        //    BlockTableRecord btr =

        //      (BlockTableRecord)tr.GetObject(

        //        bt[BlockTableRecord.ModelSpace],

        //        OpenMode.ForWrite,

        //        false

        //      );



        //    PolyFaceMesh pfm = new PolyFaceMesh();

        //    btr.AppendEntity(pfm);

        //    tr.AddNewlyCreatedDBObject(pfm, true);

        //    for (i = 0; i < npts; i++)

        //    {

        //        PolyFaceMeshVertex vert =

        //          new PolyFaceMeshVertex(

        //            new Point3d(ptx[i], pty[i], ptz[i])

        //          );

        //        pfm.AppendVertex(vert);

        //        tr.AddNewlyCreatedDBObject(vert, true);

        //    }

        //    for (i = 0; i < ntri; i++)

        //    {

        //        FaceRecord face =

        //          new FaceRecord(

        //            (short)(pt1[i] + 1),

        //            (short)(pt2[i] + 1),

        //            (short)(pt3[i] + 1),

        //            0

        //          );

        //        pfm.AppendFaceRecord(face);

        //        tr.AddNewlyCreatedDBObject(face, true);

        //    }

        //    tr.Commit();

        //}

        //if (status1 > 0)

        //    ed.WriteMessage(

        //      "\nWarning! {0} thin triangle(s) found!" +

        //      " Wrong result possible!",

        //      status1

        //    );

        Application.UpdateScreen();

    }
}
