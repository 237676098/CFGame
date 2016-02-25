#include "Cube.h"
#include "GeometryGenerator.h"
#include "TestEffect.h"

Cube::Cube() :BaseModel(), mVB(0), mIB(0)
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, I);
	XMStoreFloat4x4(&mTexTran, I);

	/*mMat.Ambient = XMFLOAT4(0.5f, 0.5f, 0.0f, 1.0f);
	mMat.Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
	mMat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);
	mMat.Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);*/

	mMat.Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mMat.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);
}

Cube::~Cube()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void Cube::Init(ID3D11Device* device)
{
	GeometryGenerator gen;
	GeometryGenerator::MeshData data;
	gen.CreateBox(100.0f, 100.0f, 100.0f, data);

	std::vector<Vertex::TestVertex> vertices(data.Vertices.size());

	for (size_t i = 0; i < data.Vertices.size(); i++)
	{
		vertices[i].Pos = data.Vertices[i].Position;
		vertices[i].Normal = data.Vertices[i].Normal;
		vertices[i].Tex = data.Vertices[i].TexC;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::TestVertex) * data.Vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(device->CreateBuffer(&vbd, &vinitData, &mVB));


	mIndexCount = data.Indices.size();

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * mIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &data.Indices[0];
	HR(device->CreateBuffer(&ibd, &iinitData, &mIB));
	

	//¼ÓÔØÎÆÀí
	HR(D3DX11CreateShaderResourceViewFromFile(device,
		L"Textures/WoodCrate01.dds", 0, 0, &mTex, 0));

	//XMMATRIX I = XMMatrixIdentity();
}


void Cube::Draw(ID3D11DeviceContext* context, BaseEffect* effect, Camera* camera, DirectionalLight* lightArr, XMFLOAT3& eyePos)
{
	context->IASetInputLayout(TestEffect::InputLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex::TestVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	context->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);


	TestEffect* testE = dynamic_cast<TestEffect*>(effect);

	assert(testE);


	D3DX11_TECHNIQUE_DESC techDesc;
	testE->getTestTech()->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		XMMATRIX world = XMLoadFloat4x4(&mWorld);
		XMMATRIX view = camera->View();
		XMMATRIX proj = camera->Proj();
		XMMATRIX worldViewProj = world*view*proj;
		XMMATRIX invTranspose = MathHelper::InverseTranspose(world);




		testE->SetWorld(world);
		testE->SetWorldViewProj(worldViewProj);
		testE->SetWorldInvTranspose(invTranspose);
		testE->SetMaterial(mMat);
		testE->getTestTech()->GetPassByIndex(p)->Apply(0, context);
		testE->SetEyePosW(eyePos);
		testE->SetDirLights(lightArr);
		testE->SetDiffuseMap(mTex);
		testE->SetTexTransform(XMLoadFloat4x4(&mTexTran));
		// 36 indices for the box.
		context->DrawIndexed(mIndexCount, 0, 0);
	}

	
	
}