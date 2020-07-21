#include "TestTerrain.h"
USING(Engine)

CTestTerrain::CTestTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{

}

CTestTerrain::CTestTerrain(const CTestTerrain & rhs)
	:CVIBuffer(rhs)
{
}

CTestTerrain::~CTestTerrain(void)
{
}

HRESULT CTestTerrain::Ready_Buffer(void)
{
	m_dwVtxCnt = m_iCX*m_iCZ;
	m_dwTriCnt = m_iCX*m_iCZ*2;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	
	VTXCOL* pVertexBuffer = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertexBuffer, 0);
	// 1. ���ؽ����� ���� ������ ���´�.
	// 2. 3��° ���ڰ��� ���� ���ؽ� �� ù ��° �ּҸ� �����Ѵ�.

	VTXCOL v;
	for (DWORD z = 0; z < m_iCX; ++z)
	{
		for (DWORD x = 0; x < m_iCZ; ++x)
		{
			v.vPosition.x = (_float)x - (m_iCZ >> 1);
			v.vPosition.y = 0.f; 
			v.vPosition.z = -((_float)z - (m_iCX >> 1));
			v.dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
			*pVertexBuffer++ = v; // ��������
		}
	}
	m_pVB->Unlock();

	INDEX16			i;
	INDEX16*		pIndex = nullptr;

	/*if (FAILED(m_pIB->Lock(0, (m_iCX - 1)*(m_iCZ - 1) * 2 * sizeof(INDEX16), (void**)&pIndex, 0)));*/
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (DWORD z = 0; z < m_iCZ - 1; z++)
	{
		for (DWORD x = 0; x < m_iCX - 1; x++)
		{
			// �»� ��ġ�� �ﰢ��
			i._0 = (z*m_iCX + x);
			i._1 = (z*m_iCX + x + 1);
			i._2 = ((z + 1)*m_iCX + x);
			// ������ ������ ���� ���� �ε��� ������ġ ����
			*pIndex++ = i;

			// ���� ��ġ�� �ﰢ��
			i._0 = ((z + 1)*m_iCX + x);
			i._1 = (z*m_iCX + x + 1);
			i._2 = ((z + 1)*m_iCX + x + 1);
			*pIndex++ = i;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void CTestTerrain::Render_Buffer(void)
{

	CVIBuffer::Render_Buffer();

}

CTestTerrain * CTestTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestTerrain*	pInstance = new CTestTerrain(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent * CTestTerrain::Clone(void)
{
	return new CTestTerrain(*this);
}

void CTestTerrain::Free(void)
{
	CVIBuffer::Free();
}
