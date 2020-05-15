//=================================================================================================
//
//  MJP's DX12 Sample Framework
//  https://github.com/TheRealMJP/DXRPathTracer/blob/master/SampleFramework12/
//
//  All code licensed under the MIT license
//
//=================================================================================================

#pragma once

#include <dxgi.h>
#include <dxgi1_6.h>
#include <dxcapi.h>
#include "../stdafx.h"

namespace SampleFramework
{
	// Common
	typedef Microsoft::WRL::ComPtr<ID3DBlob> ID3DBlobPtr;

	// DXGI
	typedef Microsoft::WRL::ComPtr<IDXGIAdapter> IDXGIAdapterPtr;
	typedef Microsoft::WRL::ComPtr<IDXGIAdapter1> IDXGIAdapter1Ptr;
	typedef Microsoft::WRL::ComPtr<IDXGIDevice> IDXGIDevicePtr;
	typedef Microsoft::WRL::ComPtr<IDXGIDevice1> IDXGIDevice1Ptr;
	typedef Microsoft::WRL::ComPtr<IDXGIDeviceSubObject> IDXGIDeviceSubObjectPtr;
	typedef Microsoft::WRL::ComPtr<IDXGIFactory> IDXGIFactoryPtr;
	typedef Microsoft::WRL::ComPtr<IDXGIFactory1> IDXGIFactory1Ptr;
	typedef Microsoft::WRL::ComPtr<IDXGIKeyedMutex> IDXGIKeyedMutexPtr;
	typedef Microsoft::WRL::ComPtr<IDXGIObject> IDXGIObjectPtr;
	typedef Microsoft::WRL::ComPtr<IDXGIOutput> IDXGIOutputPtr;
	typedef Microsoft::WRL::ComPtr<IDXGIResource> IDXGIResourcePtr;
	typedef Microsoft::WRL::ComPtr<IDXGISurface1> IDXGISurface1Ptr;
	typedef Microsoft::WRL::ComPtr<IDXGIFactory4> IDXGIFactory4Ptr;
	typedef Microsoft::WRL::ComPtr<IDXGISwapChain> IDXGISwapChainPtr;
	typedef Microsoft::WRL::ComPtr<IDXGISwapChain1> IDXGISwapChain1Ptr;
	typedef Microsoft::WRL::ComPtr<IDXGISwapChain3> IDXGISwapChain3Ptr;

	typedef Microsoft::WRL::ComPtr<IDxcBlobEncoding> IDxcBlobEncodingPtr;
	typedef Microsoft::WRL::ComPtr<IDxcOperationResult> IDxcOperationResultPtr;
	typedef Microsoft::WRL::ComPtr<IDxcBlob> IDxcBlobPtr;
	typedef Microsoft::WRL::ComPtr<IDxcCompiler> IDxcCompilerPtr;
	typedef Microsoft::WRL::ComPtr<IDxcLibrary> IDxcLibraryPtr;

	// D3D12
	typedef Microsoft::WRL::ComPtr<ID3D12CommandAllocator> ID3D12CommandAllocatorPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12CommandList> ID3D12CommandListPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList4> ID3D12GraphicsCommandList4Ptr;
	typedef Microsoft::WRL::ComPtr<ID3D12CommandQueue> ID3D12CommandQueuePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12CommandSignature> ID3D12CommandSignaturePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> ID3D12DescriptorHeapPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Device> ID3D12DevicePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Device5> ID3D12Device5Ptr;
	typedef Microsoft::WRL::ComPtr<ID3D12DeviceChild> ID3D12DeviceChildPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Fence> ID3D12FencePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> ID3D12GraphicsCommandListPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Heap> ID3D12HeapPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12StateObject> ID3D12StateObjectPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Object> ID3D12ObjectPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Object> ID3D12ObjectPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Pageable> ID3D12PageablePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12PipelineState> ID3D12PipelineStatePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12QueryHeap> ID3D12QueryHeapPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Resource> ID3D12ResourcePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12RootSignature> ID3D12RootSignaturePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12RootSignatureDeserializer> ID3D12RootSignatureDeserializerPtr;
	typedef Microsoft::WRL::ComPtr <ID3D12StateObjectProperties > ID3D12StateObjectPropertiesPtr;

	typedef Microsoft::WRL::ComPtr<ID3D12Debug> ID3D12DebugPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12Debug1> ID3D12Debug1Ptr;
	typedef Microsoft::WRL::ComPtr<ID3D12DebugDevice> ID3D12DebugDevicePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12DebugCommandList> ID3D12DebugCommandListPtr;
	typedef Microsoft::WRL::ComPtr<ID3D12DebugCommandQueue> ID3D12DebugCommandQueuePtr;
	typedef Microsoft::WRL::ComPtr<ID3D12InfoQueue> ID3D12InfoQueuePtr;
}
