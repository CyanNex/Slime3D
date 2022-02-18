#include <vulkan/mesh/Mesh.h>

cMesh::cMesh(cGeometry* pGeometry, cTexture* pTexture, cTexture* pMaterial)
{
    assert(pGeometry != nullptr);
    assert(pTexture != nullptr);
    assert(pMaterial != nullptr);

    ppGeometry = pGeometry;
    ppTexture = pTexture;
    ppMaterial = pMaterial;
}

cMesh::cMesh(cGeometry* pGeometry, cTexture* pTexture) : cMesh(pGeometry, pTexture, pTexture)
{
}

cGeometry* cMesh::GetGeometry()
{
    return ppGeometry;
}

cTexture* cMesh::GetTexture()
{
    return ppTexture;
}

cTexture* cMesh::GetMaterial()
{
    return ppMaterial;
}

void cMesh::SetTexture(cTexture* pTexture)
{
    ppTexture = pTexture;
    Invalidate();
}
