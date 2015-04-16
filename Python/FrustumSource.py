import vtk

# create a rendering window and renderer
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

# create a renderwindowinteractor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)


planesArray=range(0,24) # is there a more pythonic way to allocate a list of length 24?
camera = vtk.vtkCamera()
camera.GetFrustumPlanes(1, planesArray)
planes=vtk.vtkPlanes()
planes.SetFrustumPlanes(planesArray)

frustumSource = vtk.vtkFrustumSource()
frustumSource.SetPlanes(planes)
frustumSource.Update()

frustum = frustumSource.GetOutput()


# mapper
mapper = vtk.vtkPolyDataMapper(frustum)
mapper.SetInput(source.GetOutput())

# actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# assign actor to the renderer
ren.AddActor(actor)

# enable user interface interactor
iren.Initialize()
renWin.Render()
iren.Start()
