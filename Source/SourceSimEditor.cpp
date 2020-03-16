/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2020 Allen Institute for Brain Science and Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "SourceThread.h"
#include "SourceSimEditor.h"

SourceSimEditor::SourceSimEditor(GenericProcessor* parentNode, SourceThread* t, bool useDefaultParameterEditors)
 : VisualizerEditor(parentNode, useDefaultParameterEditors)
{

    thread = t;
    canvas = nullptr;

    tabText = "Source Sim";

	//comboBox = new ComboBox("MasterSelectComboBox");
	//addAndMakeVisible(masterSelectBox);
	
}

SourceSimEditor::~SourceSimEditor()
{

}

void SourceSimEditor::collapsedStateChanged()
{

}

void SourceSimEditor::comboBoxChanged(ComboBox* comboBox)
{


}

void SourceSimEditor::buttonEvent(Button* button)
{

}


void SourceSimEditor::saveEditorParameters(XmlElement* xml)
{
    /*
	std::cout << "Saving Neuropix editor." << std::endl;

	XmlElement* xmlNode = xml->createNewChildElement("NEUROPIXELS_EDITOR");

	for (int slot = 0; slot < thread->getNumBasestations(); slot++)
	{
		String directory_name = savingDirectories[slot].getFullPathName();
		if (directory_name.length() == 2)
			directory_name += "\\\\";
		xmlNode->setAttribute("Slot" + String(slot) + "Directory", directory_name);
	}
    */

}

void SourceSimEditor::loadEditorParameters(XmlElement* xml)
{
    /*
	forEachXmlChildElement(*xml, xmlNode)
	{
		if (xmlNode->hasTagName("NEUROPIXELS_EDITOR"))
		{
			std::cout << "Found parameters for Neuropixels editor" << std::endl;

			for (int slot = 0; slot < thread->getNumBasestations(); slot++)
			{
				File directory = File(xmlNode->getStringAttribute("Slot" + String(slot) + "Directory"));
				std::cout << "Setting thread directory for slot " << slot << std::endl;
				thread->setDirectoryForSlot(slot, directory);
				directoryButtons[slot]->setLabel(directory.getFullPathName().substring(0, 2));
				savingDirectories.set(slot, directory);
			}
		}
	}
    */
}


Visualizer* SourceSimEditor::createNewCanvas(void)
{
    std::cout << "Button clicked..." << std::endl;
    GenericProcessor* processor = (GenericProcessor*) getProcessor();
    std::cout << "Got processor." << std::endl;
    canvas = new SourceSimCanvas(processor, this, thread);
    std::cout << "Created canvas." << std::endl;
    return canvas;
}


/********************************************/

SourceSimCanvas::SourceSimCanvas(GenericProcessor* p, SourceSimEditor* editor_, SourceThread* thread) : editor(editor_)
{

    processor = (SourceNode*) p;

/*
    sourceSimViewport = new Viewport();

	XmlElement source_sim_info = thread->getInfoXml();

	if (source_sim_info.hasTagName("NEUROPIX-PXI"))
	{
		forEachXmlChildElement(source_sim_info, e)
		{
			if (e->hasTagName("BASESTATION"))
			{
				slot = e->getIntAttribute("slot");

				forEachXmlChildElement(*e, e2)
				{
					if (e2->hasTagName("PROBE"))
					{
						port = e2->getIntAttribute("port");

						std::cout << "Creating interface for " << slot << ":" << port << std::endl;

						SourceSimInterface* sourceSimInterface = new SourceSimInterface(source_sim_info, slot, port, thread, (NeuropixEditor*)p->getEditor());
						sourceSimInterfaces.add(neuropixInterface);
					}
				}
			}
		}
	}

    sourceSimViewport->setViewedComponent(sourceSimInterfaces[0], false);
    addAndMakeVisible(sourceSimViewport);
*/
    resized();
    update();
}

SourceSimCanvas::~SourceSimCanvas()
{

}

void SourceSimCanvas::paint(Graphics& g)
{
    g.fillAll(Colours::darkgrey);
}

void SourceSimCanvas::refresh()
{
    repaint();
}

void SourceSimCanvas::refreshState()
{
    resized();
}

void SourceSimCanvas::update()
{

}

void SourceSimCanvas::beginAnimation()
{
}

void SourceSimCanvas::endAnimation()
{
}

void SourceSimCanvas::resized()
{

    sourceSimViewport->setBounds(0,0,getWidth(),getHeight());

	for (int i = 0; i < sourceSimInterfaces.size(); i++)
		sourceSimInterfaces[i]->setBounds(0,0,getWidth()-sourceSimViewport->getScrollBarThickness(), 600);
}

void SourceSimCanvas::setParameter(int x, float f)
{

}

void SourceSimCanvas::setParameter(int a, int b, int c, float d)
{
}

void SourceSimCanvas::buttonClicked(Button* button)
{

}


void SourceSimCanvas::saveVisualizerParameters(XmlElement* xml)
{
	editor->saveEditorParameters(xml);

	for (int i = 0; i < sourceSimInterfaces.size(); i++)
		sourceSimInterfaces[i]->saveParameters(xml);
}

void SourceSimCanvas::loadVisualizerParameters(XmlElement* xml)
{
	editor->loadEditorParameters(xml);

	for (int i = 0; i < sourceSimInterfaces.size(); i++)
		sourceSimInterfaces[i]->loadParameters(xml);
}

/*****************************************************/
SourceSimInterface::SourceSimInterface(XmlElement info_, int _id, SourceThread* t, SourceSimEditor* e) : thread(t), editor(e), id(_id), source_sim_info(info_)
{

    cursorType = MouseCursor::NormalCursor;
    addMouseListener(this, true);

}

SourceSimInterface::~SourceSimInterface()
{

}

void SourceSimInterface::updateInfoString()
{
    /*
	String mainString;
	String infoString;

	infoString += "API Version: ";
	infoString += neuropix_info.getChildByName("API")->getStringAttribute("version", "not found");
	infoString += "\n";
	infoString += "\n";
	infoString += "\n";

	forEachXmlChildElement(source_sim_info, bs_info)
	{
		if (bs_info->hasTagName("BASESTATION"))
		{
			if (bs_info->getIntAttribute("slot") == slot)
			{
				forEachXmlChildElement(*bs_info, probe_info)
				{
					if (probe_info->getIntAttribute("port") == port)
					{
						
						infoString += "Basestation ";
						infoString += String(bs_info->getIntAttribute("index"));
						mainString += String(bs_info->getIntAttribute("index"));

					}
				}
			}
		}
	}

	infoLabel->setText(infoString, dontSendNotification);
	mainLabel->setText(mainString, dontSendNotification);
    */
}

void SourceSimInterface::comboBoxChanged(ComboBox* comboBox)
{

}

void SourceSimInterface::buttonClicked(Button* button)
{

}

void SourceSimInterface::mouseMove(const MouseEvent& event)
{


}


void SourceSimInterface::mouseUp(const MouseEvent& event)
{
    
}

void SourceSimInterface::mouseDown(const MouseEvent& event)
{

}

void SourceSimInterface::mouseDrag(const MouseEvent& event)
{
    
}

void SourceSimInterface::mouseWheelMove(const MouseEvent&  event, const MouseWheelDetails&   wheel)
{

}

MouseCursor SourceSimInterface::getMouseCursor()
{
    MouseCursor c = MouseCursor(cursorType);

    return c;
}

void SourceSimInterface::paint(Graphics& g)
{

}

void SourceSimInterface::timerCallback()
{
 
}


void SourceSimInterface::saveParameters(XmlElement* xml)
{

	std::cout << "Saving Source Sim display." << std::endl;

	//XmlElement* xmlNode = xml->createNewChildElement("PROBE");

}

void SourceSimInterface::loadParameters(XmlElement* xml)
{

}