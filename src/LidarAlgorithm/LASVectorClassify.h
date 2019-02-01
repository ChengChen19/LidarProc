#pragma once
#ifndef _LAS_VECTORCLASSIFY_H_
#define _LAS_VECTORCLASSIFY_H_

#include <map>
#include <vector>
#include "ogrsf_frmts.h"
#include "LASSimpleClassify.h"
#include "../LidarBase/LASPoint.h"
#include "../Utility/FileHelper.h"
#include "../LidarAlgorithm/WorkingConditionSimulation.h"

using namespace std;
using namespace LasAlgorithm;
//class WireModel;

class LASVectorClassify : public LASSimpleClassify
{
public:
	/**
	* Rect2D transform GDAL OGREnvelope
	* @param rect
	* @return
	*/
	OGREnvelope LASRectToEnvelope(Rect2D rect);

	/**
	* OGREnvelope transform Rect2D
	* @param m_Envelope
	* @return
	*/
	Rect2D LASEnvelopToRect(OGREnvelope *m_Envelope);

	/**
	* name tpye mapping
	* vector<string> nameKey
	* vector<eLASClassification>typeKey
	*/
	bool  LASSetMaps(vector<string> nameKey, vector<eLASClassification>typeKey);

	/**
	* Las classify by shp data
	* @param pathLas
	* @param pShpData
	* @param pathOutLas
	* @return
	*/
	virtual void LASClassifyByVector(const char* pathLas, map<string,string> pShpPath, const char* pathOutLas)=0;

    #pragma region ���ߵ��ƴ���
	/**
	* Las Point To Vector Line,
	* @param pathLas
	* @param pShpData
	* @param pathOutLas
	* @return
	*/
	void LidarToVector(vector<Point3D> pntCloud,int * pointTypes, vector<Point3D> lowerTowerPoints);

	/**
	* Las Point To Vector Line,
	* @param pathLas
	* @param pShpData
	* @param pathOutLas
	* @return 
	*/
	vector <LasAlgorithm::TensionSegment> LidarToVector(const char * pathFileConfig, string towerSpanName);

	/**
	* Vector line to Points
	* @param pathLas
	* @param pShpData
	* @param pathOutLas
	* @return
	*/
	void VectorToLidar();

	/**
	* ��֪�öε�����ʵ������������������������������ʵ�������ĵ���
	* @param pointClouds ���ߵ���
	* @param realLineCount ��ʵ������
	* @return �����ĵ���
	*/
	vector <Point3Ds> ClearSmallPoints(vector <Point3Ds> &pointClouds, long realLineCount);

	/**
	* �ָ�ֱ���������ĵ���
	* @param pointClouds ���ߵ���
	* @param tensionSeg ���Ŷ�ģ��
	* @param turnNumber ��·��
	* @return �ָ��ĵ���
	*/
	vector <Point3Ds> SegmentTangentTowerPoints(vector <Point3Ds> &pointClouds, vector <TensionSegment> &tensionSeg, long turnNumber);

	/**
	* ��ȡһ�ർ�����Ŷ�������,���������ʹ��
	* @param tensionSeg ���Ŷ�ģ��
	* @return
	*/
	void GetWholeLineSegment(vector <TensionSegment> &tensionSeg);

	/**
	* ��������ĵ���������ģ��
	* @param lineModel ��ģ��
	* @param linePoints ���ߵ���
	* @return
	*/
	void GetSectionLineModel(WireModel &lineModel,Point3Ds linePoints);

	/**
	* ��ά�����ת���ɳ߶�����S
	* @param point2D ��Ҫת���Ķ�ά��
	* @param OFootPoint ԭ��O��ֱ�ߵĴ����
	* @param lineAngle ֱ��б�ʼн�
	* @return �߶�����S
	*/
	double Point2DToScaleFactor(Point2D point2D,Point2D OFootPoint,double lineAngle);

	/**
	* �߶�����Sת���ɶ�ά�����
	* @param scaleFactor ��Ҫת���ĳ߶�����S
	* @param OFootPoint ԭ��O��ֱ�ߵĴ����
	* @param lineAngle ֱ��б�ʼн�
	* @param lineFactors ֱ�߷�������
	* @return ��ά�����
	*/
	Point2D ScaleFactorToPoint2D(double scaleFactor, Point2D OFootPoint, double lineAngle, vector <double> lineFactors);

	/**
	* ��ά�����ת����������X����
	* @param point2D ��Ҫת���Ķ�ά��
	* @param OPoint ��������ϵԭ��
	* @return ������X����
	*/
	double Point2DToSectionX(Point2D point2D, Point2D OPoint);

	/**
	* ������X����ת���ɶ�ά�����
	* @param sectoinX ������X����
	* @param OPoint ��������ϵԭ��
	* @param lineAngle ֱ��б�ʼн�
	* @return ��ά�����
	*/
	Point2D SectionXToPoint2D(double sectoinX, Point2D OPoint, double lineAngle);

	/**
	* read towerPoints from txt
	* @param pathTowerPoints
	* @param pair <Point2D,int>,type:0ֱ����,1:������
	* @return �Ƿ���ֱ����
	*/
	bool ReadTowerPointsByTxt(const char* pathTowerPoints,vector <pair <Point2D,int>> &towerPoints, vector <TensionSegment> &tensionSeg, int &towerSpanNum);

	/**
	* ���ݵ���ģ�ͺͲ���������ɵ��ߵ���
	* @param lineModel ��ģ��
	* @param sampleSpacing ���ߵ�������
	* @param isNeedSplit �Ƿ���Ҫ���ѣ�0����������ߣ�1��������ѵ���
	* @param pointOutType  ������ͣ�0:���ҷ�ƫ�㶼���,1:ֻ������ƫ��,2:ֻ����ҷ�ƫ��
	* @return ���ߵ���
	*/
	Point3Ds GetPointsByLineModel(WireModel lineModel,double sampleSpacing, int isNeedSplit, int pointOutType = 0);

	/**
	* ���ݵ���ģ�ͺͲ���������ɵ��ߵ���
	* @param tensionSeg ���Ŷ�ģ��
	* @param lineIndex  ����ģ���±�
	* @param sampleSpacing ���ߵ�������
	* @param isNeedSplit �Ƿ���Ҫ���ѣ�0����������ߣ�1��������ѵ���
	* @return ���ߵ���
	*/
	Point3Ds GetPointsByWindLineModel(TensionSegment tensionSeg, size_t lineIndex, double sampleSpacing, int isNeedSplit);

	/**
	* ���ݵ���ģ�ͼ��㵼����󻡴�
	* @param lineModel ��ģ��
	* @return ������󻡴�
	*/
	double GetWireSagByLineModel(WireModel lineModel);

	/**
	* ������Ƶ�Txt
	* @param filename  �ļ���
	* @param filePath  �ļ�·��
	* @param pntClouds ���Ƶ�
	* @return
	*/
	static void OutPoint3DsToTxt(string filename,string filePath,vector<Point3Ds> pntClouds);

	/**
	* �ӵ������ҵ�����֪������ĵ�
	* @param knownPoints  ��֪�����ݼ�
	* @param pointCloud ���Ƶ�
	* @return ����ĵ㼯
	*/
	static Point3Ds FindNearestPoint(Point3Ds knownPoints, Point3Ds pointCloud);

	/**
	* �����֪��͵��Ƶ�λ���
	* @param knownPoints  ��֪�����ݼ�
	* @param lidarPoints ���Ƶ�
	* @return 
	*/
	static void PrintPointsError(Point3Ds knownPoints, Point3Ds lidarPoints);

	void ErrorAnalysis(vector <Point3Ds> vecPoints);

	/**
	* �����ģ�͵�ʸ���ļ�SHP
	* @param filename  �ļ���
	* @param filePath  �ļ�·��
	* @param lineModel ��ģ��
	* @param sampleSpacing ���ߵ�������
	* @return
	*/
	//void OutLineModelToShp(string fileName, string filePath, WireModel lineModel, double sampleSpacing);

    #pragma endregion

	bool TestGeos();

protected:
	/*
	* trans polygon to points
	* Point2Ds points
	 * todo:
	*/
	virtual void VectorPointsToPolygon(Point2Ds points, OGRPolygon* poPolygon);

	virtual void VectorPolygonToPoints(OGRPolygon* poPolygon, Point2Ds &points);

	std::map<string, int> name_type_maps;
};


class LASShpClassify : public LASVectorClassify
{
public:

	/**
	* Las classify by shp data
	* @param pathLas
	* @param pShpPath
	* @param pathOutLas
	* @return
	*/
	void LASClassifyByVector(const char* pathLas, map<string,string> pShpPath, const char* pathOutLas);

	/** ��һ���ж��las�����ļ�����,������õ����ض�һ�������
	* Las classify by shp data
	* @param lasPaths
	* @param pShpPath
	* @param lasOutPaths
	* @param classifyType
	* @param algorithmType 0:����winding number�㷨,1:����GDAL�㷨
	* @return
	*/
	void LASClassifyBySingleTypeVector(std::vector <string> lasPaths, string lasOutPaths, string pShpPath, const char classifyType, int algorithmType = 0);
};

#endif
