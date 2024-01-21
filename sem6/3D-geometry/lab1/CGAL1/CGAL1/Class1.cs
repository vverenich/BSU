using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;

using CGALDotNet;
using CGALDotNet.Polygons;
using CGALDotNet.Hulls;
using CGALDotNetGeometry.Numerics;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.EditorInput;



namespace SharedCGAL
{
    public class CGALACAD
    {
    }
    public class Commands : IExtensionApplication
    {

        // функция инициализации (выполняется при загрузке плагина)
        public void Initialize()
        {
            MessageBox.Show("Плагин для вызова функций библиотеки CGAL");
        }

        // функция, выполняемая при выгрузке плагина
        public void Terminate()
        {
            MessageBox.Show("Выгрузка плагина для вызова функций библиотеки CGAL!");
        }

        public static Func<double[], double[], double> L2Norm_Squared_Double = (x, y) =>
        {
            double dist = Math.Sqrt(Math.Pow(x[0] - y[0], 2) + Math.Pow(x[1] - y[1], 2));
            return dist;
        };

        [CommandMethod("CGAL_Simplify", CommandFlags.Session)]
        public void CGALSimplify()
        {
            // UI to select polyline for simplification
            Database acCurDb = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Database;
            Document doc = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;
            Editor ed = doc.Editor;
            // Ask the user to select 2d polyline
            // for simplification
            PromptEntityOptions opt =
              new PromptEntityOptions(
                "\nSelect entity: "
              );
            PromptEntityResult res =
              ed.GetEntity(opt);
            if (res.Status != PromptStatus.OK)
                return;
            DBObject obj;
            Transaction tr1 = doc.TransactionManager.StartTransaction();
            using (tr1)
            {
                obj = tr1.GetObject(res.ObjectId, OpenMode.ForRead);
                // Let trunsform 
            }



            CGALDotNetGeometry.Numerics.Point2d[] points = null;
            points = new CGALDotNetGeometry.Numerics.Point2d[1];
            Polyline pl = obj as Polyline;
            if (pl == null)
            {
                MessageBox.Show("Wrong type!");
                return;
            }
            int vn = pl.NumberOfVertices;
            points = new CGALDotNetGeometry.Numerics.Point2d[vn];
            for (int ii = 0; ii < vn; ii++)
            {
                Autodesk.AutoCAD.Geometry.Point3d v3d = pl.GetPoint3dAt(ii);
                points[ii] = new CGALDotNetGeometry.Numerics.Point2d(v3d.X, v3d.Y);
            }


            Simpl form1 = new Simpl();
            if (form1.ShowDialog() == DialogResult.Cancel)
                return;

            int loc_thred = Convert.ToInt16(form1.textBoxStep.Text);

            // start simplify
            var polygon = new Polygon2<EIK>(points);
            //    var polygon = PolygonFactory<EIK>.KochStar(30, 3);
            var param = PolygonSimplificationParams.Default;
            param.threshold = loc_thred;
            param.stop = POLYGON_SIMP_STOP_FUNC.BELOW_THRESHOLD;
            param.cost = POLYGON_SIMP_COST_FUNC.SCALED_SQ_DIST;

            try
            {
                polygon.Simplify(param);
            }
            catch (Autodesk.AutoCAD.Runtime.Exception ex)
            {
                ed.WriteMessage(
                  "\nIncorrect input params",
                  ex
                );
                return;
            }



            var simplifiedPolygonPoints = new CGALDotNetGeometry.Numerics.Point2d[polygon.Count];
            polygon.GetPoints(simplifiedPolygonPoints, simplifiedPolygonPoints.Length);

            // Let save results 
            using (Transaction acTrans = acCurDb.TransactionManager.StartTransaction())
            {
                using (DocumentLock DocLock = doc.LockDocument())
                {
                    using (BlockTable acBlkTbl = acTrans.GetObject(acCurDb.BlockTableId, OpenMode.ForRead) as BlockTable)
                    {
                        using (BlockTableRecord acBlkTblRec = acTrans.GetObject(acBlkTbl[BlockTableRecord.ModelSpace], OpenMode.ForWrite) as BlockTableRecord)
                        {

                            // Create simplified polygon
                            Point3dCollection pts = new Point3dCollection();
                            for (int i = 0; i < simplifiedPolygonPoints.Length; i++)
                            {
                                Autodesk.AutoCAD.Geometry.Point3d ppp = new Autodesk.AutoCAD.Geometry.Point3d(
                                                            simplifiedPolygonPoints[i].x,
                                                            simplifiedPolygonPoints[i].y, 0);
                                if ((ppp.X != 0) && (ppp.Y != 0))
                                    pts.Add(ppp);
                            }
                            Polyline3d pline = new Polyline3d(Poly3dType.SimplePoly, pts, false);
                            pline.Closed = true;
                            acBlkTblRec.AppendEntity((Entity)pline);
                            acTrans.AddNewlyCreatedDBObject(pline, true);
                        }
                    }
                }
                acTrans.Commit();
            }

            // Let save results
        }
        [CommandMethod("CGAL_PolygonOffset", CommandFlags.Session)]
        public void CGALPolygonOffset()
        {
            // UI to select polyline for simplification
            Database acCurDb = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Database;
            Document doc = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;
            Editor ed = doc.Editor;
            // Ask the user to select 2d polyline
            // for simplification
            PromptEntityOptions opt =
              new PromptEntityOptions(
                "\nSelect entity: "
              );
            PromptEntityResult res =
              ed.GetEntity(opt);
            if (res.Status != PromptStatus.OK)
                return;
            DBObject obj;
            Transaction tr1 = doc.TransactionManager.StartTransaction();
            using (tr1)
            {
                obj = tr1.GetObject(res.ObjectId, OpenMode.ForRead);
                // Let trunsform 
            }



            CGALDotNetGeometry.Numerics.Point2d[] points = null;
            points = new CGALDotNetGeometry.Numerics.Point2d[1];
            Polyline pl = obj as Polyline;
            if (pl == null)
            {
                MessageBox.Show("Wrong type!");
                return;
            }
            int vn = pl.NumberOfVertices;
            points = new CGALDotNetGeometry.Numerics.Point2d[vn];
            for (int ii = 0; ii < vn; ii++)
            {
                Autodesk.AutoCAD.Geometry.Point3d v3d = pl.GetPoint3dAt(ii);
                points[ii] = new CGALDotNetGeometry.Numerics.Point2d(v3d.X, v3d.Y);
            }


            Simpl form1 = new Simpl();
            if (form1.ShowDialog() == DialogResult.Cancel)
                return;

            double off_set = Convert.ToDouble(form1.textBoxStep.Text);

            // start polygon offset
            var polygon = new Polygon2<EIK>(points);

            var instance = PolygonOffset2<EIK>.Instance;
            var exterior = new List<Polygon2<EIK>>();


            try
            {
                instance.CreateExteriorOffset(polygon, off_set, exterior);
            }
            catch (Autodesk.AutoCAD.Runtime.Exception ex)
            {
                ed.WriteMessage(
                  "\nIncorrect input params",
                  ex
                );
                return;
            }



            var simplifiedPolygonPoints = new CGALDotNetGeometry.Numerics.Point2d[exterior[1].Count];
            exterior[1].GetPoints(simplifiedPolygonPoints, simplifiedPolygonPoints.Length);

            // Let save results 
            using (Transaction acTrans = acCurDb.TransactionManager.StartTransaction())
            {
                using (DocumentLock DocLock = doc.LockDocument())
                {
                    using (BlockTable acBlkTbl = acTrans.GetObject(acCurDb.BlockTableId, OpenMode.ForRead) as BlockTable)
                    {
                        using (BlockTableRecord acBlkTblRec = acTrans.GetObject(acBlkTbl[BlockTableRecord.ModelSpace], OpenMode.ForWrite) as BlockTableRecord)
                        {

                            // Create simplified polygon
                            Point3dCollection pts = new Point3dCollection();
                            for (int i = 0; i < simplifiedPolygonPoints.Length; i++)
                            {
                                Autodesk.AutoCAD.Geometry.Point3d ppp = new Autodesk.AutoCAD.Geometry.Point3d(
                                                            simplifiedPolygonPoints[i].x,
                                                            simplifiedPolygonPoints[i].y, 0);
                                pts.Add(ppp);
                            }
                            Polyline3d pline = new Polyline3d(Poly3dType.SimplePoly, pts, false);
                            pline.Closed = true;
                            acBlkTblRec.AppendEntity((Entity)pline);
                            acTrans.AddNewlyCreatedDBObject(pline, true);
                        }
                    }
                }
                acTrans.Commit();
            }

            // Let save results
        }
        [CommandMethod("CGAL_ConvexHull", CommandFlags.Session)]
        public void CGALConvexHall()
        {
            // UI to select polyline for simplification
            Database acCurDb = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Database;
            Document doc = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;
            Editor ed = doc.Editor;
            // Ask the user to select 2d polyline
            // for simplification
            PromptEntityOptions opt =
              new PromptEntityOptions(
                "\nSelect entity: "
              );
            PromptEntityResult res =
              ed.GetEntity(opt);
            if (res.Status != PromptStatus.OK)
                return;
            DBObject obj;
            Transaction tr1 = doc.TransactionManager.StartTransaction();
            using (tr1)
            {
                obj = tr1.GetObject(res.ObjectId, OpenMode.ForRead);
                // Let trunsform 
            }



            CGALDotNetGeometry.Numerics.Point2d[] points = null;
            points = new CGALDotNetGeometry.Numerics.Point2d[1];
            Polyline pl = obj as Polyline;
            if (pl == null)
            {
                MessageBox.Show("Wrong type!");
                return;
            }
            int vn = pl.NumberOfVertices;
            points = new CGALDotNetGeometry.Numerics.Point2d[vn];
            for (int ii = 0; ii < vn; ii++)
            {
                Autodesk.AutoCAD.Geometry.Point3d v3d = pl.GetPoint3dAt(ii);
                points[ii] = new CGALDotNetGeometry.Numerics.Point2d(v3d.X, v3d.Y);
            }

            // start polygon offset
            var polygon = new Polygon2<EIK>();
            var convhull = new ConvexHull2<EIK>();
            try
            {
                polygon = convhull.CreateHull(points, vn);
            }
            catch (Autodesk.AutoCAD.Runtime.Exception ex)
            {
                ed.WriteMessage(
                  "\nIncorrect input params",
                  ex
                );
                return;
            }


            var simplifiedPolygonPoints = new CGALDotNetGeometry.Numerics.Point2d[polygon.Count];
            polygon.GetPoints(simplifiedPolygonPoints, simplifiedPolygonPoints.Length);

            // Let save results 
            using (Transaction acTrans = acCurDb.TransactionManager.StartTransaction())
            {
                using (DocumentLock DocLock = doc.LockDocument())
                {
                    using (BlockTable acBlkTbl = acTrans.GetObject(acCurDb.BlockTableId, OpenMode.ForRead) as BlockTable)
                    {
                        using (BlockTableRecord acBlkTblRec = acTrans.GetObject(acBlkTbl[BlockTableRecord.ModelSpace], OpenMode.ForWrite) as BlockTableRecord)
                        {

                            // Create simplified polygon
                            Point3dCollection pts = new Point3dCollection();
                            for (int i = 0; i < simplifiedPolygonPoints.Length; i++)
                            {
                                Autodesk.AutoCAD.Geometry.Point3d ppp = new Autodesk.AutoCAD.Geometry.Point3d(
                                                            simplifiedPolygonPoints[i].x,
                                                            simplifiedPolygonPoints[i].y, 0);
                                pts.Add(ppp);
                            }
                            Polyline3d pline = new Polyline3d(Poly3dType.SimplePoly, pts, false);
                            pline.Closed = true;
                            acBlkTblRec.AppendEntity((Entity)pline);
                            acTrans.AddNewlyCreatedDBObject(pline, true);
                        }
                    }
                }
                acTrans.Commit();
            }

            // Let save results
        }

        [CommandMethod("CGAL_ConvexHull_Points", CommandFlags.Session)]
        public void CGALConvexHallPoints()
        {
            Database acCurDb = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Database;
            /*
            // UI to select polyline for simplification
            Database acCurDb = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Database;
            Document doc = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;
            Editor ed = doc.Editor;
            // Ask the user to select 2d polyline
            // for simplification
            PromptEntityOptions opt =
              new PromptEntityOptions(
                "\nSelect entity: "
              );
            PromptEntityResult res =
              ed.GetEntity(opt);
            if (res.Status != PromptStatus.OK)
                return;
            DBObject obj;
            Transaction tr1 = doc.TransactionManager.StartTransaction();
            using (tr1)
            {
                obj = tr1.GetObject(res.ObjectId, OpenMode.ForRead);
                // Let trunsform 
            }
            */
            const int maxpoints = 32767;



            Document doc =

              Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument;

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

            //    int i, j, k, ntri, ned, status1 = 0, status2 = 0;
            //  bool status;

            CGALDotNetGeometry.Numerics.Point2d[] points = null;
            points = new CGALDotNetGeometry.Numerics.Point2d[npts];

            ObjectId[] idarray = ss.GetObjectIds();

            Transaction tr = db.TransactionManager.StartTransaction();
            using (tr)
            {
                DBPoint ent;
                for (int i = 0; i < npts; i++)
                {
                    ent =
                      (DBPoint)tr.GetObject(idarray[i], OpenMode.ForRead, false);


                    //  points.Add(new Point3d(ptx[i], pty[i], ptz[i]));
                    points[i] = new CGALDotNetGeometry.Numerics.Point2d(ent.Position[0], ent.Position[1]);

                    // points[i].Add(new Vector3d(ptx[i], pty[i], ptz[i]));


                }

                tr.Commit();

            }

            /*
            points = new CGALDotNetGeometry.Numerics.Point2d[1];
            Polyline pl = obj as Polyline;
            if (pl == null)
            {
                MessageBox.Show("Wrong type!");
                return;
            }
            int vn = pl.NumberOfVertices;
            points = new CGALDotNetGeometry.Numerics.Point2d[vn];
            for (int ii = 0; ii < vn; ii++)
            {
                Autodesk.AutoCAD.Geometry.Point3d v3d = pl.GetPoint3dAt(ii);
                points[ii] = new CGALDotNetGeometry.Numerics.Point2d(v3d.X, v3d.Y);
            }
            */



            // start polygon offset
            var polygon = new Polygon2<EIK>();
            var convhull = new ConvexHull2<EIK>();
            try
            {
                polygon = convhull.CreateHull(points, npts);
            }
            catch (Autodesk.AutoCAD.Runtime.Exception ex)
            {
                ed.WriteMessage(
                  "\nIncorrect input params",
                  ex
                );
                return;
            }


            var simplifiedPolygonPoints = new CGALDotNetGeometry.Numerics.Point2d[polygon.Count];
            polygon.GetPoints(simplifiedPolygonPoints, simplifiedPolygonPoints.Length);

            // Let save results 
            using (Transaction acTrans = acCurDb.TransactionManager.StartTransaction())
            {
                using (DocumentLock DocLock = doc.LockDocument())
                {
                    using (BlockTable acBlkTbl = acTrans.GetObject(acCurDb.BlockTableId, OpenMode.ForRead) as BlockTable)
                    {
                        using (BlockTableRecord acBlkTblRec = acTrans.GetObject(acBlkTbl[BlockTableRecord.ModelSpace], OpenMode.ForWrite) as BlockTableRecord)
                        {

                            // Create simplified polygon
                            Point3dCollection pts = new Point3dCollection();
                            for (int i = 0; i < simplifiedPolygonPoints.Length; i++)
                            {
                                Autodesk.AutoCAD.Geometry.Point3d ppp = new Autodesk.AutoCAD.Geometry.Point3d(
                                                            simplifiedPolygonPoints[i].x,
                                                            simplifiedPolygonPoints[i].y, 0);
                                pts.Add(ppp);
                            }
                            Polyline3d pline = new Polyline3d(Poly3dType.SimplePoly, pts, false);
                            pline.Closed = true;
                            acBlkTblRec.AppendEntity((Entity)pline);
                            acTrans.AddNewlyCreatedDBObject(pline, true);
                        }
                    }
                }
                acTrans.Commit();
            }

            // Let save results
        }

    }
}