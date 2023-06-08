





void CExam_19_P30CodeNevisirDoc::OnOpenImage()
{
	CFileDialog fdlg(true, _T("*.jpg"), 0, OFN_EXPLORER, _T("All Supported Formats(*.jpg, *.bmp, *.tif, *.png)|*.jpg;*.bmp;*.tif;*.png|Jpeg Files(*.jpg)|*.jpg||"));
	if(fdlg.DoModal() == IDOK){
		img.Load(fdlg.GetFileName());
		UpdateAllViews(0);
	}
}

void CExam_19_P30CodeNevisirDoc::OnProcessRotate()
{
	CRotateDlg *pDlg = new CRotateDlg(AfxGetMainWnd());
	if(pDlg->DoModal() == IDOK){
		img.Rotate(pDlg->m_dAnlge);
		UpdateAllViews(0);
	}
	CxImage fftImageR, fftImageI;
	img.FFT2(&img, 0, &fftImageR, &fftImageI);
	img.Copy(fftImageI);
}

void CExam_19_P30CodeNevisirDoc::OnSaveImage()
{
	CFileDialog fdlg(false, _T("*.jpg"), 0, OFN_EXPLORER, _T("All Supported Formats(*.jpg, *.bmp, *.tif, *.png)|*.jpg;*.bmp;*.tif;*.png|Jpeg Files(*.jpg)|*.jpg||"));
	if(fdlg.DoModal() == IDOK){
		img.Save(fdlg.GetFileName(), CXIMAGE_FORMAT_BMP);
	}	

	/*CImage img2;
	int arr[256] = {0};
	img.Create(img2.GetWidth(), img2.GetHeight(), img2.GetBpp());
	for (int y = 0; y < img.GetHeight(); y++){
		byte* ptr = img.GetBits(y);
		byte* ptr2 = img2.GetPixelAddress(0, y);
		memcpy(ptr2, ptr, img.GetWidth()*3);
	}
	*/
}
