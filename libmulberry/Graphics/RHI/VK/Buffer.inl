namespace mulberry::vk
{
    template <typename T>
    CpuBuffer::CpuBuffer(const std::vector<T> &srcData, BufferUsage usage)
        : Buffer(srcData.data(), sizeof(T) * srcData.size(), usage, MemoryProperty::HOST_VISIBLE | MemoryProperty::HOST_COHERENT)
    {
    }

    template <typename T>
    inline VertexBuffer::VertexBuffer(const std::vector<T> &vertices)
        : GpuBuffer(sizeof(T) * vertices.size(), BufferUsage::TRANSFER_DST | BufferUsage::VERTEX)
    {
        Fill(vertices);
    }

    template <typename T>
    inline void VertexBuffer::Fill(const std::vector<T> &inputArray)
    {
        mSize = inputArray.size();
        uint64_t bufferSize = sizeof(T) * inputArray.size();
        CpuBuffer stagingBuffer = CpuBuffer(bufferSize, BufferUsage::TRANSFER_SRC);

        stagingBuffer.Fill(bufferSize, inputArray.data());

        UploadDataFrom(bufferSize, stagingBuffer);
    }

    template <typename T>
    inline IndexBuffer::IndexBuffer(const std::vector<T> &indices)
        : GpuBuffer(sizeof(T) * indices.size(), BufferUsage::TRANSFER_DST | BufferUsage::INDEX)
    {
        Fill(indices);
    }

    template <typename T>
    inline void IndexBuffer::Fill(const std::vector<T> &input)
    {
        mSize = input.size();
        mDataType = DataStr2VkIndexType(typeid(T).name());
        uint64_t bufferSize = sizeof(T) * input.size();
        CpuBuffer stagingBuffer = CpuBuffer(bufferSize, BufferUsage::TRANSFER_SRC);
        stagingBuffer.Fill(bufferSize, input.data());
        UploadDataFrom(bufferSize, stagingBuffer);
    }

    template <typename T>
    inline ShaderStorageBuffer::ShaderStorageBuffer(const std::vector<T> &bufferData)
        : GpuBuffer(sizeof(T) * bufferData.size(), BufferUsage::TRANSFER_DST | BufferUsage::STORAGE)
    {
        uint64_t bufferSize = sizeof(T) * bufferData.size();
        CpuBuffer stagingBuffer = CpuBuffer(bufferSize, BufferUsage::TRANSFER_SRC);
        stagingBuffer.Fill(bufferSize, bufferData.data());

        UploadDataFrom(bufferSize, stagingBuffer);
    }

    template <typename T>
    inline UniformBuffer<T>::UniformBuffer()
        : CpuBuffer(sizeof(T), BufferUsage::UNIFORM)
    {
    }

    template <typename T>
    inline void UniformBuffer<T>::Fill(const T &data)
    {
        this->Fill(sizeof(T), (void *)&data);
    }
}